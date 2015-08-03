// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

part of glfw;

///  Wraps the output of the C API's `glfwGetVersion`
class GLFWVersion {
  final int major;
  final int minor;
  final int rev;
  GLFWVersion(this.major, this.minor, this.rev);
}

/// Returns a [GLFWVersion] instance which has [major], [minor], [rev] fields.
GLFWVersion glfwGetVersion() native "glfwGetVersion";

/// Returns a [List<GLFWmonitor>] instance.
List<GLFWmonitor> glfwGetMonitors() native "glfwGetMonitors";

/// Returns a [Point] instance.
Point glfwGetMonitorPos(GLFWmonitor monitor) native "glfwGetMonitorPos";

/// Returns a [Rectangle] instance with [xpos] and [ypos] set to 0.
Rectangle glfwGetMonitorPhysicalSize(
    GLFWmonitor monitor) native "glfwGetMonitorPhysicalSize";

/// Returns a [List<GLFWvidmode>] instance.
List<GLFWvidmode> glfwGetVideoModes(
    GLFWmonitor monitor) native "glfwGetVideoModes";

/// Returns a [Point] instance.
Point glfwGetWindowPos(GLFWwindow window) native "glfwGetWindowPos";

/// Returns a [Rectangle] instance with [xpos] and [ypos] set to 0.
Rectangle glfwGetWindowSize(GLFWwindow window) native "glfwGetWindowSize";

/// Returns a [Rectangle] instance with [xpos] and [ypos] set to 0.
Rectangle glfwGetFramebufferSize(
    GLFWwindow window) native "glfwGetFramebufferSize";

/// Returns a [Rectangle] instance.
Rectangle glfwGetWindowFrameSize(
    GLFWwindow window) native "glfwGetWindowFrameSize";

/// [pointer] parameter is a Dart [Object].
void glfwSetWindowUserPointer(
    GLFWwindow window, Object pointer) native "glfwSetWindowUserPointer";

/// Returns an [Object] instance.
Object glfwGetWindowUserPointer(
    GLFWwindow window) native "glfwGetWindowUserPointer";

/// Returns a [Point] instance.
Point glfwGetCursorPos(GLFWwindow window) native "glfwGetCursorPos";

/// Returns a [List<double>] instance.
List<double> glfwGetJoystickAxes(int joy) native "glfwGetJoystickAxes";

/// Returns a [List<int>] instance.
List<int> glfwGetJoystickButtons(int joy) native "glfwGetJoystickButtons";
