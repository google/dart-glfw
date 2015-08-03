// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef SRC_GLFW_EXTENSION_H_
#define SRC_GLFW_EXTENSION_H_

#include "dart_api.h"

extern Dart_Handle GLFWLibrary;
extern Dart_Handle MathLibrary;

Dart_NativeFunction ResolveName(Dart_Handle name, int argc,
                                bool* auto_setup_scope);

DART_EXPORT Dart_Handle glfw_extension_Init(Dart_Handle parent_library);

#endif  // SRC_GLFW_EXTENSION_H_
