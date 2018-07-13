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
Point<int> glfwGetMonitorPos(GLFWmonitor monitor) native "glfwGetMonitorPos";

/// Returns a [Rectangle] instance with [xpos] and [ypos] set to 0.
Rectangle<int> glfwGetMonitorPhysicalSize(GLFWmonitor monitor)
    native "glfwGetMonitorPhysicalSize";

/// Returns a [List<GLFWvidmode>] instance.
List<GLFWvidmode> glfwGetVideoModes(GLFWmonitor monitor)
    native "glfwGetVideoModes";

/// Returns a [Point] instance.
Point<int> glfwGetWindowPos(GLFWwindow window) native "glfwGetWindowPos";

/// Returns a [Rectangle] instance with [xpos] and [ypos] set to 0.
Rectangle<int> glfwGetWindowSize(GLFWwindow window) native "glfwGetWindowSize";

/// Returns a [Rectangle] instance with [xpos] and [ypos] set to 0.
Rectangle<int> glfwGetFramebufferSize(GLFWwindow window)
    native "glfwGetFramebufferSize";

/// Returns a [Rectangle] instance.
Rectangle<int> glfwGetWindowFrameSize(GLFWwindow window)
    native "glfwGetWindowFrameSize";

/// [pointer] parameter is a Dart [Object].
void glfwSetWindowUserPointer(GLFWwindow window, Object pointer)
    native "glfwSetWindowUserPointer";

/// Returns an [Object] instance.
Object glfwGetWindowUserPointer(GLFWwindow window)
    native "glfwGetWindowUserPointer";

/// Returns a [Point] instance.
Point<int> glfwGetCursorPos(GLFWwindow window) native "glfwGetCursorPos";

/// Returns a [List<double>] instance.
List<double> glfwGetJoystickAxes(int joy) native "glfwGetJoystickAxes";

/// Returns a [List<int>] instance.
List<int> glfwGetJoystickButtons(int joy) native "glfwGetJoystickButtons";

// Async calls.
SendPort _swapBuffersPort;

/// Sets up a service port for async requests to glfwSwapBufers().
SendPort createSwapBuffersServicePort() native "CreateSwapBuffersServicePort";

/// Makes an asynchronous call to glfwSwapBuffers().
///
/// The returned [Future] will complete when the native call is finished.
///
/// NOTE: There must not be any GL context bound before calling
/// glfwSwapBuffersAsync(). This is because glfwSwapBuffersAsync() will attempt
/// to acquire the context before swapping (a requirement for the implicit
/// glFlush() performed by the SwapBuffers call).
///
/// A typical usage pattern is:
///
/// ```
/// glfwMakeContextCurrent(window);
///
/// // (perform rendering)
///
/// glfwMakeContextCurrent(null);
/// await glfwSwapBuffers(window);
/// ```
Future glfwSwapBuffersAsync(GLFWwindow window) async {
  assert(glfwGetCurrentContext() == null,
      "glfwSwapBuffersAsync() requires the current context to be null.");

  // Set up the Dart Port to handle swap buffers calls, if necessary.
  _swapBuffersPort ??= createSwapBuffersServicePort();

  // Send the SendPort and arguments to the native function wrapper.
  int windowPtr = window._native_pointer;
  await _asyncCall(_swapBuffersPort, [windowPtr]);
}

/// Helper for asynchronous calls.
Future _asyncCall(SendPort sendPort, Iterable args) async {
  // Create the port that will receive the results from the native call.
  var replyPort = new ReceivePort();

  // Create the argument list, placing the sending side of the reply port
  // first, followed by the given arguments.
  var argsList = <dynamic>[replyPort.sendPort];
  argsList.addAll(args);

  // Send the arguments to invoke the function that is bound to the given
  // SendPort.
  sendPort.send(argsList);

  // Wait for the result, and return it.
  return await replyPort.first;
}
