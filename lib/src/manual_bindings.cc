// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd#include <stdio.h>

// This file contains native extension functions which have to be manually
// written due to the corresponding C functions returning values via pointer
// arguments.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GLFW/glfw3.h>
#include <dart_api.h>

#include "instantiate_glfw_classes.h"
#include "manual_bindings.h"
#include "util.h"

void glfwGetVersion_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwGetVersion_);
  int major, minor, rev;
  glfwGetVersion(&major, &minor, &rev);
  Dart_SetReturnValue(arguments, NewGLFWVersion(major, minor, rev));
  TRACE_END(glfwGetVersion_);
}

void glfwGetMonitors_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwGetMonitors_);
  int count;
  GLFWmonitor** monitors = glfwGetMonitors(&count);

  if (monitors == NULL) {
    Dart_SetReturnValue(arguments, Dart_Null());
    return;
  }

  Dart_Handle monlist = Dart_NewList(count);
  for (int i = 0; i < count; i++) {
    Dart_ListSetAt(monlist, i, NewGLFWmonitor(monitors[i]));
  }

  Dart_SetReturnValue(arguments, monlist);
  TRACE_END(glfwGetMonitors_);
}

void glfwGetMonitorPos_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwGetMonitorPos_);
  Dart_Handle monitor_obj = HANDLE(Dart_GetNativeArgument(arguments, 0));

  GLFWmonitor* monitor = GetNativePointer<GLFWmonitor>(monitor_obj);

  int xpos, ypos;
  glfwGetMonitorPos(monitor, &xpos, &ypos);

  Dart_SetReturnValue(arguments, NewPoint(xpos, ypos));
  TRACE_END(glfwGetMonitorPos_);
}

void glfwGetMonitorPhysicalSize_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwGetMonitorPhysicalSize_);
  Dart_Handle monitor_obj = HANDLE(Dart_GetNativeArgument(arguments, 0));

  GLFWmonitor* monitor = GetNativePointer<GLFWmonitor>(monitor_obj);

  int widthMM, heightMM;
  glfwGetMonitorPhysicalSize(monitor, &widthMM, &heightMM);
  Dart_SetReturnValue(arguments, NewRectangle(0, 0, widthMM, heightMM));
  TRACE_END(glfwGetMonitorPhysicalSize_);
}

void glfwGetVideoModes_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwGetVideoModes_);
  Dart_Handle monitor_obj = HANDLE(Dart_GetNativeArgument(arguments, 0));

  GLFWmonitor* monitor = GetNativePointer<GLFWmonitor>(monitor_obj);

  int count;
  const GLFWvidmode* vidmodes = glfwGetVideoModes(monitor, &count);

  Dart_Handle vidlist = Dart_NewList(count);
  for (int i = 0; i < count; i++) {
    Dart_ListSetAt(vidlist, i, NewGLFWvidmode(&vidmodes[i]));
  }
  Dart_SetReturnValue(arguments, vidlist);
  TRACE_END(glfwGetVideoModes_);
}

void glfwGetWindowPos_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwGetWindowPos_);
  Dart_Handle window_obj = HANDLE(Dart_GetNativeArgument(arguments, 0));

  GLFWwindow* window = GetNativePointer<GLFWwindow>(window_obj);

  int x, y;
  glfwGetWindowPos(window, &x, &y);

  Dart_SetReturnValue(arguments, NewPoint(x, y));
  TRACE_END(glfwGetWindowPos_);
}

void glfwGetWindowSize_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwGetWindowSize_);
  Dart_Handle window_obj = HANDLE(Dart_GetNativeArgument(arguments, 0));

  GLFWwindow* window = GetNativePointer<GLFWwindow>(window_obj);

  int width, height;
  glfwGetWindowSize(window, &width, &height);

  Dart_SetReturnValue(arguments, NewRectangle(0, 0, width, height));
  TRACE_END(glfwGetWindowSize_);
}

void glfwGetFramebufferSize_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwGetFramebufferSize_);
  Dart_Handle window_obj = HANDLE(Dart_GetNativeArgument(arguments, 0));

  GLFWwindow* window = GetNativePointer<GLFWwindow>(window_obj);

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  Dart_SetReturnValue(arguments, NewRectangle(0, 0, width, height));
  TRACE_END(glfwGetFramebufferSize_);
}

void glfwGetWindowFrameSize_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwGetWindowFrameSize_);
  Dart_Handle window_obj = HANDLE(Dart_GetNativeArgument(arguments, 0));

  GLFWwindow* window = GetNativePointer<GLFWwindow>(window_obj);

  int left, top, width, height;
  glfwGetWindowFrameSize(window, &left, &top, &width, &height);

  Dart_SetReturnValue(arguments, NewRectangle(left, top, width, height));
  TRACE_END(glfwGetWindowFrameSize_);
}

void glfwSetWindowUserPointer_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwSetWindowUserPointer_);
  Dart_Handle window_obj = HANDLE(Dart_GetNativeArgument(arguments, 0));
  Dart_Handle object_obj = HANDLE(Dart_GetNativeArgument(arguments, 1));

  GLFWwindow* window = GetNativePointer<GLFWwindow>(window_obj);

  Dart_PersistentHandle* cur = reinterpret_cast<Dart_PersistentHandle*>(
      glfwGetWindowUserPointer(window));
  if (cur != NULL) {
    Dart_DeletePersistentHandle(*cur);
  }
  Dart_PersistentHandle new_handle =
      HANDLE(Dart_NewPersistentHandle(object_obj));

  glfwSetWindowUserPointer(window, new_handle);
  TRACE_END(glfwSetWindowUserPointer_);
}

void glfwGetWindowUserPointer_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwGetWindowUserPointer_);
  Dart_Handle window_obj = HANDLE(Dart_GetNativeArgument(arguments, 0));

  GLFWwindow* window = GetNativePointer<GLFWwindow>(window_obj);

  Dart_PersistentHandle* cur = reinterpret_cast<Dart_PersistentHandle*>(
      glfwGetWindowUserPointer(window));
  if (cur == NULL) {
    Dart_SetReturnValue(arguments, Dart_Null());
  } else {
    Dart_SetReturnValue(arguments, *cur);
  }
  TRACE_END(glfwGetWindowUserPointer_);
}

void glfwGetCursorPos_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwGetCursorPos_);
  Dart_Handle window_obj = HANDLE(Dart_GetNativeArgument(arguments, 0));

  GLFWwindow* window = GetNativePointer<GLFWwindow>(window_obj);

  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  Dart_SetReturnValue(arguments, NewPoint(xpos, ypos));
  TRACE_END(glfwGetCursorPos_);
}

void glfwGetJoystickAxes_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwGetJoystickAxes_);
  int64_t joy;
  HANDLE(Dart_GetNativeIntegerArgument(arguments, 0, &joy));

  int count;
  const float* axes = glfwGetJoystickAxes(joy, &count);

  Dart_Handle axislist = Dart_NewList(count);
  for (int i = 0; i < count; i++) {
    Dart_ListSetAt(axislist, i, Dart_NewDouble(axes[i]));
  }
  Dart_SetReturnValue(arguments, axislist);
  TRACE_END(glfwGetJoystickAxes_);
}

void glfwGetJoystickButtons_native(Dart_NativeArguments arguments) {
  TRACE_START(glfwGetJoystickButtons_);
  int64_t joy;
  HANDLE(Dart_GetNativeIntegerArgument(arguments, 0, &joy));

  int count;
  const unsigned char* buttons = glfwGetJoystickButtons(joy, &count);

  Dart_Handle buttonlist = Dart_NewList(count);
  for (int i = 0; i < count; i++) {
    Dart_ListSetAt(buttonlist, i, Dart_NewInteger(buttons[i]));
  }
  Dart_SetReturnValue(arguments, buttonlist);
  TRACE_END(glfwGetJoystickButtons_);
}

void PostNull(Dart_Port reply_port) {
  Dart_CObject reply;
  reply.type = Dart_CObject_kNull;
  Dart_PostCObject(reply_port, &reply);
}

void glfwSwapBuffers_wrapper(Dart_Port dest_port, Dart_CObject* message) {
  if (message->type != Dart_CObject_kArray ||
      message->value.as_array.length != 2) {
    fprintf(stderr, "Incorrect data type or length in message.\n");
    return;
  }

  Dart_CObject* param0 = message->value.as_array.values[0];
  if (param0->type != Dart_CObject_kSendPort) {
    fprintf(stderr, "Expected a SendPort as the first argument.\n");
    return;
  }
  Dart_Port reply_port = param0->value.as_send_port.id;

  Dart_CObject* param1 = message->value.as_array.values[1];
  GLFWwindow* window;
  switch (param1->type) {
    case Dart_CObject_kInt32:
      window = reinterpret_cast<GLFWwindow*>(param1->value.as_int32);
      break;
    case Dart_CObject_kInt64:
      window = reinterpret_cast<GLFWwindow*>(param1->value.as_int64);
      break;
    default:
      fprintf(stderr,
              "Expected an int64 or int32 as the second argument, is: %d.\n",
              param1->type);
      PostNull(reply_port);
      return;
  }
  if (window == NULL) {
    fprintf(stderr, "Window is null.\n");
    PostNull(reply_port);
    return;
  }

  // Acquire the context, then swap buffers on the window.
  glfwMakeContextCurrent(window);
  glfwSwapBuffers(window);
  glfwMakeContextCurrent(NULL);

  // Post the reply indicating we're done.
  PostNull(reply_port);
}
