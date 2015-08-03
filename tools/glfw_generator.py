# Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
# Please see the AUTHORS file for details. Use of this source code is governed
# by a BSD-style license that can be found in the LICENSE file or at
# https://developers.google.com/open-source/licenses/bsd

# pylint: disable=superfluous-parens
# Parenthesis around print statements are fine.
"""Generator script for the GLFW extension.

Rather than running this script directly, consider running genbindings.sh if you
have clang-formatter and dartfmt installed.

This script does not generate the entire project, only function_list.h,
function_list.cc, glfw_bindings.h, glfw_bindings.cc, glfw_native_functions.dart,
and glfw_constants.dart.
"""

import sys

from default_generator.extension_generator import DefaultExtensionGenerator
from glfw_templates import *
from glfw_type_maps import *

# These functions have manual bindings defined in lib/src/manual_bindings.cc
HAS_MANUAL_BINDINGS = [
    "glfwGetVersion",
    "glfwGetMonitors",
    "glfwGetMonitorPos",
    "glfwGetMonitorPhysicalSize",
    "glfwGetVideoModes",
    "glfwGetWindowPos",
    "glfwGetWindowSize",
    "glfwGetFramebufferSize",
    "glfwGetWindowFrameSize",
    "glfwSetWindowUserPointer",
    "glfwGetWindowUserPointer",
    "glfwGetCursorPos",
    "glfwGetJoystickAxes",
    "glfwGetJoystickButtons",
]


class GLFWExtensionGenerator(DefaultExtensionGenerator):
  """This class automatically generates GLFW extension code.

  It genererates the C extension and Dart declarations, and the C definitions.

  All functions besides init and generate_bindings are essentially private. You
    may call them, but at your own risk.

  Below attributes are those in addition to DefaultExtensionGenerator's.

  Attributes:
    callback_arg_exceptions: A dict of GLFW callback type:callback handler
      definitions for callbacks with tricky type signatures.
    callback_handler_hint_map: The equivalent of arg_hint_map for
      callback handlers.
  """

  c_callback_typedefs_map = glfw_c_callback_typedefs_map
  dart_callback_typedefs_map = glfw_dart_callback_typedefs_map

  def __init__(self, constant_defines, function_declarations,
               has_manual_bindings=None):
    """Inits the GLFWExtensionGenerator.

    Args:
      constant_defines: A list of C define statements that should be parsed into
          Dart constants.
      function_declarations: A list of C function declarations to generate a
         Dart native extension from.
      has_manual_bindings: A list of C function names that already have manual
          bindings.
    """
    self.callback_arg_exceptions = dict()
    self.callback_handler_hint_map = dict()

    super(GLFWExtensionGenerator, self).__init__(
        constant_defines, function_declarations, has_manual_bindings=has_manual_bindings)

  def parse_functions(self):
    self.dart_callback_typedefs = self.generate_callback_typedefs()
    super(GLFWExtensionGenerator, self).parse_functions()

  def generate_callback_typedefs(self):
    """Generate a list of Dart typedefs for GLFW callbacks."""
    typedefs = list()
    for function_name, args in self.dart_callback_typedefs_map.items():
      arguments = list()
      for arg in args:
        if " ".join(arg) in self.callback_handler_hint_map:
          arguments.append(
              self.callback_handler_hint_map[" ".join(arg)] + " " + arg[-1])
        else:
          arguments.append(" ".join(arg))
      typedefs.append("typedef void {function_name}({arguments});".format(
          function_name=function_name,
          arguments=", ".join(arguments)))

    return typedefs

  def generate_callback_handler(self, c_function):
    """Generates a C GLFW callback handler for a glfwSet*Callback function.

    Args:
      c_function: A CFunction object.
    Returns:
      A C handler function for a GLFW callback.
    """
    c_callback_type = c_function.c_ret_type
    dart_callback_type = self.type_map[c_callback_type]

    c_arguments = list()
    dart_handle_arguments_array = list()

    if c_callback_type in self.callback_arg_exceptions:
      return self.callback_arg_exceptions[c_callback_type]

    for i, arg in enumerate(
        self.c_callback_typedefs_map[c_callback_type]):
      c_type = arg[0]
      c_arg = arg[1]

      new_handle_call = str()
      if " ".join(arg) in self.callback_handler_hint_map:
        new_handle_call = self.new_handle_map[
            self.callback_handler_hint_map[" ".join(arg)]].format(ret=c_arg)
      else:
        new_handle_call = self.new_handle_map[c_type].format(ret=c_arg)

      c_arguments.append(" ".join(arg))
      dart_handle_arguments_array.append(
          GLFW_ARGUMENTS_ARRAY_TEMPLATE.format(
              i=i,
              new_handle_call=new_handle_call))

    return DART_CALLBACK_HANDLER_TEMPLATE.format(
        callback_type=dart_callback_type,
        c_arguments=", ".join(c_arguments),
        num_arguments=len(self.dart_callback_typedefs_map[dart_callback_type]),
        create_dart_argument_handles="\n  ".join(dart_handle_arguments_array))

  def generate_glfw_callback_definition(self, c_function):
    """Generates a C extension function for glfwSet*Callback functions.

    Args:
      c_function: A CFunction object.
    Returns:
      A C extension function for a glfwSet*Callback function.
    """
    function_name = c_function.function_name
    extension_function_name = c_function.extension_function_name
    callback_type = c_function.c_ret_type

    arguments = [arg[1] for arg in c_function.c_arguments]

    # switch cbfun variable name to _{callback_type}_cb
    arguments = [
        "_" + callback_type + "_cb" if (arg == "cbfun") else arg
        for arg in arguments
    ]

    get_native_arguments = list()
    for i, arg in enumerate(c_function.c_arguments):
      if arg[1] == "cbfun":
        get_native_arguments.append(
            DART_CALLBACK_HANDLE_ARGUMENT_TEMPLATE.format(
                callback_type=callback_type,
                i=i))
      else:
        get_native_arguments.append(
            self.dart_handle_to_c_variable(i, arg,
                                           c_function.dart_arguments[i]))

    return GLFW_CALLBACK_BINDING_TEMPLATE.format(
        extension_function_name=extension_function_name,
        function_name=function_name,
        get_native_arguments="\n  ".join(get_native_arguments),
        callback_type=callback_type,
        arguments=", ".join(arguments))

  def bind_function(self, c_function):
    """Generate extension declarations and definitions from a C function.

    Args:
      c_function: A CFunction object.
    """
    if c_function.c_ret_type in self.c_callback_typedefs_map:
      self.dart_extension_declarations.append(
          self.generate_dart_declaration(c_function))
      self.c_extension_declarations.append(
          self.generate_c_extension_declaration(c_function))
      definition = self.generate_callback_handler(c_function)
      self.c_extension_definitions.append(self.format_definition(definition))

      definition = self.generate_glfw_callback_definition(c_function)
      self.c_extension_definitions.append(self.format_definition(definition))
    else:
      super(GLFWExtensionGenerator, self).bind_function(c_function)


def main():
  if len(sys.argv) != 2:
    print("This script takes a single argument, the location of your system's "
          "glfw3.h header file.")
    return

  header_file = None
  try:
    header_file = open(sys.argv[1], "r")
  except IOError as err:
    print(err)
    return

  const_lines = list()

  api_lines = list()

  for line in header_file:
    if line.startswith("#define GLFW_"):
      const_lines.append(line.strip())
    elif line.startswith("GLFWAPI "):
      api_lines.append(line.strip().replace("GLFWAPI ", ""))

  glfw_gen = GLFWExtensionGenerator(
      constant_defines=const_lines,
      function_declarations=api_lines,
      has_manual_bindings=HAS_MANUAL_BINDINGS)
  glfw_gen.type_map.update(glfw_type_map)
  glfw_gen.handle_to_c_map.update(glfw_handle_c_map)
  glfw_gen.new_handle_map.update(glfw_new_handle_map)
  glfw_gen.ret_hint_map.update(glfw_return_type_hint_map)
  glfw_gen.needs_free_map.update(glfw_needs_free_map)
  glfw_gen.callback_arg_exceptions.update(glfw_callback_arguments_exceptions)
  glfw_gen.callback_handler_hint_map.update(
      glfw_dart_handler_arguments_hint_map)
  glfw_gen.generate_bindings()

  print("Writing function_list.h...")
  with open("generated/function_list.h", "w") as f:
    f.write(GLFW_FUNCTION_LIST_HEADER_BODY)

  print("Writing function_list.cc...")
  with open("generated/function_list.cc", "w") as f:
    f.write(GLFW_FUNCTION_LIST_HEADER)
    f.write("\n".join(glfw_gen.function_list))
    f.write(GLFW_FUNCTION_LIST_FOOTER)

  print("Writing glfw_bindings.h...")
  with open("generated/glfw_bindings.h", "w") as f:
    f.write(GLFW_GENERATED_BINDINGS_HEADER_HEADER)
    f.write("// Header file for generated GLFW function bindings.\n\n")
    f.write("\n".join(glfw_gen.c_extension_declarations))
    f.write(GLFW_GENERATED_BINDINGS_HEADER_FOOTER)

  print("Writing glfw_bindings.cc...")
  with open("generated/glfw_bindings.cc", "w") as f:
    f.write(GLFW_GENERATED_BINDINGS_HEADER)
    f.write("// Generated GLFW function bindings for Dart.\n\n")
    f.write("\n".join(glfw_gen.c_extension_definitions))

  print("Writing glfw_native_functions.dart...")
  with open("generated/glfw_native_functions.dart", "w") as f:
    f.write(GLFW_DART_GENERATED_FUNCTIONS_HEADER)
    f.write("/// Dart definitions for GLFW native extension.\n\n")
    f.write("\n".join(glfw_gen.dart_callback_typedefs))
    f.write("\n\n")
    f.write("\n".join(glfw_gen.dart_extension_declarations))

  print("Writing glfw_constants.dart...")
  with open("generated/glfw_constants.dart", "w") as f:
    f.write(GLFW_DART_GENERATED_CONSTANTS_HEADER)
    f.write("/// Generated GLFW constants.\n\n")
    f.write("\n".join(glfw_gen.dart_constants))
    f.write("\n\n")
  print("")

  print("THESE REQUIRE MANUAL BINDING:")
  for func in glfw_gen.c_functions:
    if func.needs_manual_bindings and not func.has_manual_bindings:
      print(func)
  print("")
  print("")


if __name__ == "__main__":
  main()
