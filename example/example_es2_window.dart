// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

/// This program draws an example window with a OpenGL ES 2 context.
/// It outputs the window position when the window is moved,
/// the cursor position when the window is clicked,
/// prints printable characters when they are typed and the window has focus,
/// and additionally prints a newline when the enter key is pressed.

import 'package:glfw/glfw.dart';

import 'dart:io';

void winMoveCallback(GLFWwindow win, int xpos, int ypos) {
  print("$xpos $ypos");
}

void winClickCallback(GLFWwindow win, int button, int action, int mods) {
  print(glfwGetCursorPos(win));
}

void charCallback(GLFWwindow win, int codepoint) {
  stdout.write(new String.fromCharCode(codepoint));
}

void keypressCallback(
    GLFWwindow win, int key, int scancode, int action, int mods) {
  if ((action == GLFW_PRESS) && (key == GLFW_KEY_ENTER)) {
    stdout.write("\n");
  }
}

main() async {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);

  GLFWwindow window = glfwCreateWindow(640, 480, "Hello Dart GLFW", null, null);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  glfwSetWindowPosCallback(window, winMoveCallback);
  glfwSetMouseButtonCallback(window, winClickCallback);

  glfwSetCharCallback(window, charCallback);
  glfwSetKeyCallback(window, keypressCallback);

  while (!glfwWindowShouldCloseAsBool(window)) {
    // Context can be activated for drawing...
    glfwMakeContextCurrent(window);

    glfwPollEvents();

    // Must release context before calling glfwSwapBuffersAsync().
    glfwMakeContextCurrent(null);

    // Wait for buffer swap.
    await glfwSwapBuffersAsync(window);
  }
  glfwTerminate();
}
