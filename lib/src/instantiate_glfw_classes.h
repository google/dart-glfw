// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef SRC_INSTANTIATE_GLFW_CLASSES_H_
#define SRC_INSTANTIATE_GLFW_CLASSES_H_

#include "GLFW/glfw3.h"
#include "dart_api.h"

Dart_Handle NewPoint(int x, int y);
Dart_Handle NewRectangle(int left, int top, int width, int height);

Dart_Handle NewGLFWwindow(GLFWwindow *window);
Dart_Handle NewGLFWmonitor(GLFWmonitor *monitor);
Dart_Handle NewGLFWcursor(GLFWcursor *cursor);
Dart_Handle NewGLFWvidmode(const GLFWvidmode *vidmode);
Dart_Handle NewGLFWgammaramp(const GLFWgammaramp *gammaramp);
Dart_Handle NewGLFWimage(const GLFWimage *image);
Dart_Handle NewGLFWVersion(int major, int minor, int rev);

GLFWvidmode *NewGLFWvidmodeFromDart(Dart_Handle vidmode_handle);
GLFWgammaramp *NewGLFWgammarampFromDart(Dart_Handle gammaramp_handle);
GLFWimage *NewGLFWimageFromDart(Dart_Handle image_handle);

#endif  // SRC_INSTANTIATE_GLFW_CLASSES_H_
