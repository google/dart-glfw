// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

// This file contains GLFW-independent utility functions for
// Dart native extensions.

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "GLFW/glfw3.h"
#include "dart_api.h"
#include "dart_native_api.h"

#include "manual_bindings.h"
#include "util.h"

Dart_Handle HandleError(Dart_Handle handle) {
  if (Dart_IsError(handle)) {
    Dart_PropagateError(handle);
  }
  return handle;
}

Dart_Handle Dart_IntegerToInt(Dart_Handle integer, int* value) {
  int64_t actual;
  HandleError(Dart_IntegerToInt64(integer, &actual));

  if (actual < INT_MAX) {
    *value = static_cast<int>(actual);
    return Dart_True();
  } else {
    char buf[50];  // Technically we only need 46 characters for this.
    snprintf(buf, sizeof(buf), "%" PRId64 " does not fit into an int.", actual);
    return Dart_NewApiError(buf);
  }
}

// NOLINTNEXTLINE
Dart_Handle Dart_IntegerToUShort(Dart_Handle integer, unsigned short* value) {
  int64_t actual;
  HandleError(Dart_IntegerToInt64(integer, &actual));

  if (actual < USHRT_MAX) {  // NOLINTNEXTLINE
    *value = static_cast<unsigned short>(actual);
    return Dart_True();
  } else {
    char buf[50];  // Technically we only need 46 characters for this.
    snprintf(buf, sizeof(buf),
             "%" PRId64 " does not fit into an unsigned short.", actual);
    return Dart_NewApiError(buf);
  }
}

Dart_Handle Dart_IntegerToUInt(Dart_Handle integer, unsigned int* value) {
  int64_t actual;
  HandleError(Dart_IntegerToInt64(integer, &actual));

  if (actual < UINT_MAX) {
    *value = static_cast<unsigned int>(actual);
    return Dart_True();
  } else {
    char buf[50];  // Technically we only need 46 characters for this.
    snprintf(buf, sizeof(buf), "%" PRId64 " does not fit into an unsigned int.",
             actual);
    return Dart_NewApiError(buf);
  }
}

Dart_Handle Dart_IntegerToUChar(Dart_Handle integer, unsigned char* value) {
  int64_t actual;
  HandleError(Dart_IntegerToInt64(integer, &actual));

  if (actual < UCHAR_MAX) {
    *value = static_cast<unsigned char>(actual);
    return Dart_True();
  } else {
    char buf[50];  // Technically we only need 46 characters for this.
    snprintf(buf, sizeof(buf),
             "%" PRId64 " does not fit into an unsigned char.", actual);
    return Dart_NewApiError(buf);
  }
}

void CreateSwapBuffersServicePort(Dart_NativeArguments args) {
  // Default to returning null.
  Dart_SetReturnValue(args, Dart_Null());

  // Create a ReceivePort to take requests to swap buffers.
  Dart_Port service_port = Dart_NewNativePort("glfwSwapBuffers_wrapper",
                                              glfwSwapBuffers_wrapper, true);

  // If the new port is valid, return the send port that Dart code can use
  // to make swap buffers requests.
  if (service_port != ILLEGAL_PORT) {
    Dart_Handle send_port = Dart_NewSendPort(service_port);
    Dart_SetReturnValue(args, send_port);
  }
}
