# Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
# Please see the AUTHORS file for details. Use of this source code is governed
# by a BSD-style license that can be found in the LICENSE file or at
# https://developers.google.com/open-source/licenses/bsd
"""Custom type maps for the GLFW extension generator.

Extra maps include the typedefs_maps and the handler arg type map.
"""

# pylint: disable=wildcard-import
from glfw_templates import *

glfw_dart_callback_typedefs_map = {
    "GLFWerrorfun": [["int", "error"], ["String", "description"]],
    "GLFWwindowposfun": [["GLFWwindow", "window"], ["int", "xpos"], ["int",
                                                                     "ypos"]],
    "GLFWwindowsizefun": [["GLFWwindow", "window"], ["int", "width"],
                          ["int", "height"]],
    "GLFWwindowclosefun": [["GLFWwindow", "window"]],
    "GLFWwindowrefreshfun": [["GLFWwindow", "window"]],
    "GLFWwindowfocusfun": [["GLFWwindow", "window"], ["int", "focused"]],
    "GLFWwindowiconifyfun": [["GLFWwindow", "window"], ["int", "iconified"]],
    "GLFWframebuffersizefun": [["GLFWwindow", "window"], ["int", "width"],
                               ["int", "height"]],
    "GLFWmousebuttonfun": [["GLFWwindow", "window"], ["int", "button"],
                           ["int", "action"], ["int", "mods"]],
    "GLFWcursorposfun": [["GLFWwindow", "window"], ["double", "xpos"],
                         ["double", "ypos"]],
    "GLFWcursorenterfun": [["GLFWwindow", "window"], ["int", "entered"]],
    "GLFWscrollfun": [["GLFWwindow", "window"], ["double", "xoffset"],
                      ["double", "yoffset"]],
    "GLFWkeyfun": [["GLFWwindow", "window"], ["int", "key"],
                   ["int", "scancode"], ["int", "action"], ["int", "mods"]],
    "GLFWcharfun": [["GLFWwindow", "window"], ["int", "codepoint"]],
    "GLFWcharmodsfun": [["GLFWwindow", "window"], ["int", "codepoint"],
                        ["int", "mods"]],
    "GLFWdropfun": [["GLFWwindow", "window"], ["int", "count"], ["List<String>",
                                                                 "paths"]],
    "GLFWmonitorfun": [["GLFWmonitor", "monitor"], ["int", "event"]],
}

glfw_c_callback_typedefs_map = {
    "GLFWerrorfun": [["int", "error"], ["const char*", "description"]],
    "GLFWwindowposfun": [["GLFWwindow*", "window"], ["int", "xpos"], ["int",
                                                                      "ypos"]],
    "GLFWwindowsizefun": [["GLFWwindow*", "window"], ["int", "width"],
                          ["int", "height"]],
    "GLFWwindowclosefun": [["GLFWwindow*", "window"]],
    "GLFWwindowrefreshfun": [["GLFWwindow*", "window"]],
    "GLFWwindowfocusfun": [["GLFWwindow*", "window"], ["int", "focused"]],
    "GLFWwindowiconifyfun": [["GLFWwindow*", "window"], ["int", "iconified"]],
    "GLFWframebuffersizefun": [["GLFWwindow*", "window"], ["int", "width"],
                               ["int", "height"]],
    "GLFWmousebuttonfun": [["GLFWwindow*", "window"], ["int", "button"],
                           ["int", "action"], ["int", "mods"]],
    "GLFWcursorposfun": [["GLFWwindow*", "window"], ["double", "xpos"],
                         ["double", "ypos"]],
    "GLFWcursorenterfun": [["GLFWwindow*", "window"], ["int", "entered"]],
    "GLFWscrollfun": [["GLFWwindow*", "window"], ["double", "xoffset"],
                      ["double", "yoffset"]],
    "GLFWkeyfun": [["GLFWwindow*", "window"], ["int", "key"],
                   ["int", "scancode"], ["int", "action"], ["int", "mods"]],
    "GLFWcharfun": [["GLFWwindow*", "window"], ["unsigned int", "codepoint"]],
    "GLFWcharmodsfun": [["GLFWwindow*", "window"],
                        ["unsigned int", "codepoint"], ["int", "mods"]],
    "GLFWdropfun": [["GLFWwindow*", "window"], ["int", "count"],
                    ["const char**", "paths"]],
    "GLFWmonitorfun": [["GLFWmonitor*", "monitor"], ["int", "event"]],
}

glfw_callback_arguments_exceptions = {
    "GLFWdropfun": """static Dart_Handle dart_GLFWdropfun_cb = NULL;

void _GLFWdropfun_cb(GLFWwindow* window, int count, const char** paths) {
  Dart_Handle arguments[3];
  arguments[0] = HandleError(NewGLFWwindow(window));
  arguments[1] = HandleError(Dart_NewInteger(count));
  arguments[2] = HandleError(Dart_NewList(count));
  for (int i = 0; i<count; i++) {
    HandleError(Dart_ListSetAt(arguments[2], i, Dart_NewStringFromCString(paths[i])));
  }
  HandleError(Dart_InvokeClosure(dart_GLFWscrollfun_cb, 3, arguments));
}
"""
}

glfw_dart_handler_arguments_hint_map = dict()
glfw_dart_handler_arguments_hint_map.update({
    "int focused": "bool",
    "int iconified": "bool",
    "int entered": "bool",
})
glfw_dart_handler_arguments_hint_map.update({
    "unsigned int codepoint": "int",
})

glfw_type_map = dict()
glfw_type_map.update({
    "GLFWmonitor*": "GLFWmonitor",
    "GLFWwindow*": "GLFWwindow",
    "GLFWcursor*": "GLFWcursor",
    "const GLFWvidmode*": "GLFWvidmode",
    "const GLFWgammaramp*": "GLFWgammaramp",
    "const GLFWimage*": "GLFWimage",
})
glfw_type_map.update({
    "GLFWerrorfun": "GLFWerrorfun",
    "GLFWmonitorfun": "GLFWmonitorfun",
    "GLFWwindowposfun": "GLFWwindowposfun",
    "GLFWwindowsizefun": "GLFWwindowsizefun",
    "GLFWwindowclosefun": "GLFWwindowclosefun",
    "GLFWwindowrefreshfun": "GLFWwindowrefreshfun",
    "GLFWwindowfocusfun": "GLFWwindowfocusfun",
    "GLFWwindowiconifyfun": "GLFWwindowiconifyfun",
    "GLFWframebuffersizefun": "GLFWframebuffersizefun",
    "GLFWkeyfun": "GLFWkeyfun",
    "GLFWcharfun": "GLFWcharfun",
    "GLFWcharmodsfun": "GLFWcharmodsfun",
    "GLFWmousebuttonfun": "GLFWmousebuttonfun",
    "GLFWcursorposfun": "GLFWcursorposfun",
    "GLFWcursorenterfun": "GLFWcursorenterfun",
    "GLFWscrollfun": "GLFWscrollfun",
    "GLFWdropfun": "GLFWdropfun",
})

glfw_handle_c_map = dict()
glfw_handle_c_map.update({
    "GLFWmonitor": MONITOR_HANDLE_TO_C_VAR_TEMPLATE,
    "GLFWwindow": WINDOW_HANDLE_TO_C_VAR_TEMPLATE,
    "GLFWcursor": CURSOR_HANDLE_TO_C_VAR_TEMPLATE,
    "GLFWvidmore": VIDMODE_HANDLE_TO_C_VAR_TEMPLATE,
    "GLFWgammaramp": GAMMARAMP_HANDLE_TO_C_VAR_TEMPLATE,
    "GLFWimage": IMAGE_HANDLE_TO_C_VAR_TEMPLATE,
})

glfw_new_handle_map = dict()
glfw_new_handle_map.update({
    "GLFWmonitor*": "NewGLFWmonitor({ret})",
    "GLFWwindow*": "NewGLFWwindow({ret})",
    "GLFWcursor*": "NewGLFWcursor({ret})",
    "const GLFWvidmode*": "NewGLFWvidmode({ret})",
    "const GLFWgammaramp*": "NewGLFWgammaramp({ret})",
    "const GLFWimage*": "NewGLFWimage({ret})",
})

glfw_needs_free_map = dict()
glfw_needs_free_map.update({
    "GLFWvidmode": GLFWVIDMODE_FREE_TEMPLATE,
    "GLFWgammaramp": GLFWGAMMARAMP_FREE_TEMPLATE,
    "GLFWimage": GLFWIMAGE_FREE_TEMPLATE,
})

glfw_return_type_hint_map = dict()
glfw_return_type_hint_map.update({
    "glfwInit": "bool",
    "glfwJoystickPresent": "bool",
    "glfwExtensionSupported": "bool",
})
