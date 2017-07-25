// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#include <stdio.h>
#include <string.h>

#include <dart_api.h>
#include <GLFW/glfw3.h>

#include "generated/function_list.h"
#include "generated/glfw_bindings.h"
#include "glfw_extension.h"
#include "manual_bindings.h"
#include "util.h"

Dart_Handle GLFWLibrary;
Dart_Handle MathLibrary;

DART_EXPORT Dart_Handle glfw_extension_Init(Dart_Handle parent_library) {
  if (Dart_IsError(parent_library)) {
    return parent_library;
  }

  Dart_Handle result_code =
      Dart_SetNativeResolver(parent_library, ResolveName, NULL);
  if (Dart_IsError(result_code)) {
    return result_code;
  }

  GLFWLibrary =
      HandleError(Dart_NewPersistentHandle(HandleError(Dart_LookupLibrary(
          Dart_NewStringFromCString("package:glfw/glfw.dart")))));
  MathLibrary = HandleError(Dart_NewPersistentHandle(
      HandleError(Dart_LookupLibrary(Dart_NewStringFromCString("dart:math")))));

  return Dart_Null();
}

Dart_NativeFunction ResolveName(Dart_Handle name, int argc,
                                bool* auto_setup_scope) {
  if (!Dart_IsString(name)) {
    return NULL;
  }
  Dart_NativeFunction result = NULL;

  const char* cname;
  HandleError(Dart_StringToCString(name, &cname));

  for (int i = 0; function_list[i].name != NULL; ++i) {
    if (strcmp(function_list[i].name, cname) == 0) {
      result = function_list[i].function;
      break;
    }
  }

  if (result == NULL) {
    // Didn't find it in the function list. Try service port functions.
    if (strcmp("CreateSwapBuffersServicePort", cname) == 0) {
      result = CreateSwapBuffersServicePort;
    }
  }

  return result;
}
