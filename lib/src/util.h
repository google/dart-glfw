// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include "dart_api.h"

template <typename T>
Dart_Handle NewDartIntList(int size, T* array);

Dart_Handle HandleError(Dart_Handle handle);

Dart_Handle Dart_IntegerToInt(Dart_Handle integer, int* value);
// NOLINTNEXTLINE
Dart_Handle Dart_IntegerToUShort(Dart_Handle integer, unsigned short* value);
Dart_Handle Dart_IntegerToUInt(Dart_Handle integer, unsigned int* value);
Dart_Handle Dart_IntegerToUChar(Dart_Handle integer, unsigned char* value);

#endif  // SRC_UTIL_H_
