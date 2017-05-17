// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

/// A Dart library which uses a native extension to call C GLFW functions.
///
/// GLFW is a cross-platform library for creating windows with OpenGL contexts
/// and receiving input and events.
///
/// Please see the README.md and especially the official
/// [GLFW documentation](http://www.glfw.org/docs/latest/index.html)
/// for more detail.
library glfw;

import 'dart:async';
import 'dart:isolate';

import 'dart-ext:glfw_extension';

import 'dart:math' show Point, Rectangle;

export 'src/generated/glfw_constants.dart';

part 'src/glfw_classes.dart';
part 'src/manual_bindings.dart';
part 'src/generated/glfw_native_functions.dart';

/// Checks the close flag of the specified [GLFWwindow] and returns either
/// [true] or [false].
///
/// [glfwWindowShouldClose] may return any [int], but typically returns 0 or 1.
/// In Dart, `!(1)` returns [true], so in order to be able to write
///     `if (!glfwWindowShouldClose(window)) {}`
/// this convenience function is required and should be used instead.
/// This function throws a [StateError] if [glfwWindowShouldClose] returns
/// any value other than 0 or 1.
bool glfwWindowShouldCloseAsBool(GLFWwindow window) {
  int shouldClose = glfwWindowShouldClose(window);
  if (shouldClose == 0) {
    return false;
  } else if (shouldClose == 1) {
    return true;
  } else {
    throw new StateError(
        "glfwWindowShouldClose flag was $shouldClose, not 0 or 1. It is "
        "likely this is due to a glfwSetWindowShouldClose call elsewhere "
        "in the program.");
  }
}
