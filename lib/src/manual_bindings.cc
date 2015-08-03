// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd#include <stdio.h>

// This file contains native extension functions which have to be manually
// written due to the corresponding C functions returning values via pointer
// arguments.

#include <string.h>
#include <stdlib.h>

#include "GLFW/glfw3.h"
#include "dart_api.h"

#include "instantiate_glfw_classes.h"
#include "util.h"
#include "manual_bindings.h"

void glfwGetVersion_native(Dart_NativeArguments arguments) {
  int major, minor, rev;
  glfwGetVersion(&major, &minor, &rev);
  Dart_SetReturnValue(arguments, NewGLFWVersion(major, minor, rev));
}

void glfwGetMonitors_native(Dart_NativeArguments arguments) {
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
}

void glfwGetMonitorPos_native(Dart_NativeArguments arguments) {
  Dart_Handle monitor_obj = HandleError(Dart_GetNativeArgument(arguments, 0));

  GLFWmonitor* monitor = NULL;
  if (!Dart_IsNull(monitor_obj)) {
    HandleError(Dart_GetNativeInstanceField(
        monitor_obj, 0, reinterpret_cast<intptr_t*>(&monitor)));
  }

  int xpos, ypos;
  glfwGetMonitorPos(monitor, &xpos, &ypos);

  Dart_SetReturnValue(arguments, NewPoint(xpos, ypos));
}

void glfwGetMonitorPhysicalSize_native(Dart_NativeArguments arguments) {
  Dart_Handle monitor_obj = HandleError(Dart_GetNativeArgument(arguments, 0));

  GLFWmonitor* monitor = NULL;
  if (!Dart_IsNull(monitor_obj)) {
    HandleError(Dart_GetNativeInstanceField(
        monitor_obj, 0, reinterpret_cast<intptr_t*>(&monitor)));
  }

  int widthMM, heightMM;
  glfwGetMonitorPhysicalSize(monitor, &widthMM, &heightMM);
  Dart_SetReturnValue(arguments, NewRectangle(0, 0, widthMM, heightMM));
}

void glfwGetVideoModes_native(Dart_NativeArguments arguments) {
  Dart_Handle monitor_obj = HandleError(Dart_GetNativeArgument(arguments, 0));

  GLFWmonitor* monitor = NULL;
  if (!Dart_IsNull(monitor_obj)) {
    HandleError(Dart_GetNativeInstanceField(
        monitor_obj, 0, reinterpret_cast<intptr_t*>(&monitor)));
  }

  int count;
  const GLFWvidmode* vidmodes = glfwGetVideoModes(monitor, &count);

  Dart_Handle vidlist = Dart_NewList(count);
  for (int i = 0; i < count; i++) {
    Dart_ListSetAt(vidlist, i, NewGLFWvidmode(&vidmodes[i]));
  }
  Dart_SetReturnValue(arguments, vidlist);
}

void glfwGetWindowPos_native(Dart_NativeArguments arguments) {
  Dart_Handle window_obj = HandleError(Dart_GetNativeArgument(arguments, 0));

  GLFWwindow* window = NULL;
  if (!Dart_IsNull(window_obj)) {
    HandleError(Dart_GetNativeInstanceField(
        window_obj, 0, reinterpret_cast<intptr_t*>(&window)));
  }

  int x, y;
  glfwGetWindowPos(window, &x, &y);

  Dart_SetReturnValue(arguments, NewPoint(x, y));
}

void glfwGetWindowSize_native(Dart_NativeArguments arguments) {
  Dart_Handle window_obj = HandleError(Dart_GetNativeArgument(arguments, 0));

  GLFWwindow* window = NULL;
  if (!Dart_IsNull(window_obj)) {
    HandleError(Dart_GetNativeInstanceField(
        window_obj, 0, reinterpret_cast<intptr_t*>(&window)));
  }

  int width, height;
  glfwGetWindowSize(window, &width, &height);

  Dart_SetReturnValue(arguments, NewRectangle(0, 0, width, height));
}

void glfwGetFramebufferSize_native(Dart_NativeArguments arguments) {
  Dart_Handle window_obj = HandleError(Dart_GetNativeArgument(arguments, 0));

  GLFWwindow* window = NULL;
  if (!Dart_IsNull(window_obj)) {
    HandleError(Dart_GetNativeInstanceField(
        window_obj, 0, reinterpret_cast<intptr_t*>(&window)));
  }

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  Dart_SetReturnValue(arguments, NewRectangle(0, 0, width, height));
}

void glfwGetWindowFrameSize_native(Dart_NativeArguments arguments) {
  Dart_Handle window_obj = HandleError(Dart_GetNativeArgument(arguments, 0));

  GLFWwindow* window = NULL;
  if (!Dart_IsNull(window_obj)) {
    HandleError(Dart_GetNativeInstanceField(
        window_obj, 0, reinterpret_cast<intptr_t*>(&window)));
  }

  int left, top, width, height;
  glfwGetWindowFrameSize(window, &left, &top, &width, &height);

  Dart_SetReturnValue(arguments, NewRectangle(left, top, width, height));
}

void glfwSetWindowUserPointer_native(Dart_NativeArguments arguments) {
  Dart_Handle window_obj = HandleError(Dart_GetNativeArgument(arguments, 0));
  Dart_Handle object_obj = HandleError(Dart_GetNativeArgument(arguments, 1));

  GLFWwindow* window = NULL;
  if (!Dart_IsNull(window_obj)) {
    HandleError(Dart_GetNativeInstanceField(
        window_obj, 0, reinterpret_cast<intptr_t*>(&window)));
  }

  Dart_PersistentHandle* cur = reinterpret_cast<Dart_PersistentHandle*>(
      glfwGetWindowUserPointer(window));
  if (cur != NULL) {
    Dart_DeletePersistentHandle(*cur);
  }
  Dart_PersistentHandle new_handle =
      HandleError(Dart_NewPersistentHandle(object_obj));

  glfwSetWindowUserPointer(window, new_handle);
}

void glfwGetWindowUserPointer_native(Dart_NativeArguments arguments) {
  Dart_Handle window_obj = HandleError(Dart_GetNativeArgument(arguments, 0));

  GLFWwindow* window = NULL;
  if (!Dart_IsNull(window_obj)) {
    HandleError(Dart_GetNativeInstanceField(
        window_obj, 0, reinterpret_cast<intptr_t*>(&window)));
  }

  Dart_PersistentHandle* cur = reinterpret_cast<Dart_PersistentHandle*>(
      glfwGetWindowUserPointer(window));
  if (cur == NULL) {
    Dart_SetReturnValue(arguments, Dart_Null());
  } else {
    Dart_SetReturnValue(arguments, *cur);
  }
}

void glfwGetCursorPos_native(Dart_NativeArguments arguments) {
  Dart_Handle window_obj = HandleError(Dart_GetNativeArgument(arguments, 0));

  GLFWwindow* window = NULL;
  if (!Dart_IsNull(window_obj)) {
    HandleError(Dart_GetNativeInstanceField(
        window_obj, 0, reinterpret_cast<intptr_t*>(&window)));
  }

  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  Dart_SetReturnValue(arguments, NewPoint(xpos, ypos));
}

void glfwGetJoystickAxes_native(Dart_NativeArguments arguments) {
  int64_t joy;
  HandleError(Dart_GetNativeIntegerArgument(arguments, 0, &joy));

  int count;
  const float* axes = glfwGetJoystickAxes(joy, &count);

  Dart_Handle axislist = Dart_NewList(count);
  for (int i = 0; i < count; i++) {
    Dart_ListSetAt(axislist, i, Dart_NewDouble(axes[i]));
  }
  Dart_SetReturnValue(arguments, axislist);
}

void glfwGetJoystickButtons_native(Dart_NativeArguments arguments) {
  int64_t joy;
  HandleError(Dart_GetNativeIntegerArgument(arguments, 0, &joy));

  int count;
  const unsigned char* buttons = glfwGetJoystickButtons(joy, &count);

  Dart_Handle buttonlist = Dart_NewList(count);
  for (int i = 0; i < count; i++) {
    Dart_ListSetAt(buttonlist, i, Dart_NewInteger(buttons[i]));
  }
  Dart_SetReturnValue(arguments, buttonlist);
}
