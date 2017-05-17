// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include "dart_api.h"

#if defined(GLFW_TRACING)
#include "third_party/dart_lang/runtime/include/dart_tools_api.h"
#define TRACE_START(name)                                \
  Dart_TimelineEvent(#name, Dart_TimelineGetMicros(), 0, \
                     Dart_Timeline_Event_Begin, 0, NULL, NULL)
#define TRACE_END(name)                                  \
  Dart_TimelineEvent(#name, Dart_TimelineGetMicros(), 0, \
                     Dart_Timeline_Event_End, 0, NULL, NULL)
#else
#define TRACE_START(name) \
  do {                    \
  } while (0)
#define TRACE_END(name) \
  do {                  \
  } while (0)
#endif

#if defined(GLFW_TESTING)
#define HANDLE(handle) HandleError(handle)
#else
#define HANDLE(handle) handle
#endif

// Constructs a new Dart List of integers with the given size and data.
template <typename T>
Dart_Handle NewDartIntList(int size, T* array) {
  Dart_Handle list_handle = Dart_NewList(size);
  for (int i = 0; i < size; i++) {
    Dart_ListSetAt(list_handle, i,
                   Dart_NewInteger(static_cast<int64_t>(array[i])));
  }
  return list_handle;
}

// Extracts a pointer to a GLFW object from a Dart wrapper class.
template <typename T>
T* GetNativePointer(Dart_Handle obj) {
  if (Dart_IsNull(obj)) {
    return nullptr;
  }
  Dart_Handle wrapper =
      HANDLE(Dart_GetField(obj, Dart_NewStringFromCString("_native_pointer")));
  int64_t native_value;
  HANDLE(Dart_IntegerToInt64(wrapper, &native_value));
  intptr_t ptr_value = static_cast<intptr_t>(native_value);
  return reinterpret_cast<T*>(ptr_value);
}

Dart_Handle HandleError(Dart_Handle handle);

Dart_Handle Dart_IntegerToInt(Dart_Handle integer, int* value);
// NOLINTNEXTLINE
Dart_Handle Dart_IntegerToUShort(Dart_Handle integer, unsigned short* value);
Dart_Handle Dart_IntegerToUInt(Dart_Handle integer, unsigned int* value);
Dart_Handle Dart_IntegerToUChar(Dart_Handle integer, unsigned char* value);

void CreateSwapBuffersServicePort(Dart_NativeArguments args);

#endif  // SRC_UTIL_H_
