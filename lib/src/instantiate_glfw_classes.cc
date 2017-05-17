// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

// This file contains functions to instantiate Dart GLFW classes from C structs
// and C structs from corresponding Dart classes. Additionally it contains
// NewPoint and NewRectangle for instantiating those Dart classes from
// dart:math.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GLFW/glfw3.h"
#include "dart_api.h"

#include "glfw_extension.h"
#include "instantiate_glfw_classes.h"
#include "util.h"

// NOTE: In every case where cpplint is disabled in this file, it is because
// GLFW structs use "unsigned short", "unsigned char", etc. instead of int16,
// int8, etc.

Dart_Handle NewPoint(int x, int y) {
  Dart_Handle Point_type = HandleError(
      Dart_GetType(MathLibrary, Dart_NewStringFromCString("Point"), 0, NULL));

  Dart_Handle arguments[2];
  arguments[0] = Dart_NewInteger(x);
  arguments[1] = Dart_NewInteger(y);

  return HandleError(Dart_New(Point_type, Dart_Null(), 2, arguments));
}

Dart_Handle NewRectangle(int left, int top, int width, int height) {
  Dart_Handle Rectangle_type = HandleError(Dart_GetType(
      MathLibrary, Dart_NewStringFromCString("Rectangle"), 0, NULL));

  Dart_Handle arguments[4];
  arguments[0] = Dart_NewInteger(left);
  arguments[1] = Dart_NewInteger(top);
  arguments[2] = Dart_NewInteger(width);
  arguments[3] = Dart_NewInteger(height);

  return HandleError(Dart_New(Rectangle_type, Dart_Null(), 4, arguments));
}

Dart_Handle NewGLFWwindow(GLFWwindow *window) {
  if (window == NULL) return Dart_Null();

  Dart_Handle GLFWwindow_type = HandleError(Dart_GetType(
      GLFWLibrary, Dart_NewStringFromCString("GLFWwindow"), 0, NULL));

  Dart_Handle args[1];
  intptr_t ptr_value = reinterpret_cast<intptr_t>(window);
  args[0] = Dart_NewInteger(static_cast<int64_t>(ptr_value));
  return HandleError(Dart_New(GLFWwindow_type, Dart_Null(), 1, args));
}

Dart_Handle NewGLFWmonitor(GLFWmonitor *monitor) {
  Dart_Handle GLFWmonitor_type = HandleError(Dart_GetType(
      GLFWLibrary, Dart_NewStringFromCString("GLFWmonitor"), 0, NULL));

  Dart_Handle args[1];
  intptr_t ptr_value = reinterpret_cast<intptr_t>(monitor);
  args[0] = Dart_NewInteger(static_cast<int64_t>(ptr_value));
  return HandleError(Dart_New(GLFWmonitor_type, Dart_Null(), 1, args));
}

Dart_Handle NewGLFWcursor(GLFWcursor *cursor) {
  Dart_Handle GLFWcursor_type = HandleError(Dart_GetType(
      GLFWLibrary, Dart_NewStringFromCString("GLFWcursor"), 0, NULL));

  Dart_Handle args[1];
  intptr_t ptr_value = reinterpret_cast<intptr_t>(cursor);
  args[0] = Dart_NewInteger(static_cast<int64_t>(ptr_value));
  return HandleError(Dart_New(GLFWcursor_type, Dart_Null(), 1, args));
}

Dart_Handle NewGLFWvidmode(const GLFWvidmode *vidmode) {
  Dart_Handle GLFWvidmode_type = HandleError(Dart_GetType(
      GLFWLibrary, Dart_NewStringFromCString("GLFWvidmode"), 0, NULL));

  Dart_Handle arguments[6];
  arguments[0] = Dart_NewInteger(vidmode->width);
  arguments[1] = Dart_NewInteger(vidmode->height);
  arguments[2] = Dart_NewInteger(vidmode->redBits);
  arguments[3] = Dart_NewInteger(vidmode->greenBits);
  arguments[4] = Dart_NewInteger(vidmode->blueBits);
  arguments[5] = Dart_NewInteger(vidmode->refreshRate);

  return HandleError(Dart_New(GLFWvidmode_type, Dart_Null(), 6, arguments));
}

Dart_Handle NewGLFWgammaramp(const GLFWgammaramp *gammaramp) {
  Dart_Handle GLFWgammaramp_type = HandleError(Dart_GetType(
      GLFWLibrary, Dart_NewStringFromCString("GLFWgammaramp"), 0, NULL));

  int size = gammaramp->size;

  Dart_Handle arguments[4];
  // NOLINTNEXTLINE
  arguments[0] = NewDartIntList<unsigned short>(size, gammaramp->red);
  // NOLINTNEXTLINE
  arguments[1] = NewDartIntList<unsigned short>(size, gammaramp->green);
  // NOLINTNEXTLINE
  arguments[2] = NewDartIntList<unsigned short>(size, gammaramp->blue);
  arguments[3] = Dart_NewInteger(gammaramp->size);

  return HandleError(Dart_New(GLFWgammaramp_type, Dart_Null(), 4, arguments));
}

Dart_Handle NewGLFWimage(const GLFWimage *image) {
  Dart_Handle GLFWimage_type = HandleError(Dart_GetType(
      GLFWLibrary, Dart_NewStringFromCString("GLFWimage"), 0, NULL));

  // I believe this is RGBA
  int size = (image->width) * (image->height) * 4;

  Dart_Handle arguments[3];
  arguments[0] = Dart_NewInteger(image->width);
  arguments[1] = Dart_NewInteger(image->height);
  arguments[2] = NewDartIntList<unsigned char>(size, image->pixels);

  return HandleError(Dart_New(GLFWimage_type, Dart_Null(), 3, arguments));
}

Dart_Handle NewGLFWVersion(int major, int minor, int rev) {
  Dart_Handle GLFWVersion_type = HandleError(Dart_GetType(
      GLFWLibrary, Dart_NewStringFromCString("GLFWVersion"), 0, NULL));

  Dart_Handle arguments[3];
  arguments[0] = Dart_NewInteger(major);
  arguments[1] = Dart_NewInteger(minor);
  arguments[2] = Dart_NewInteger(rev);

  return HandleError(Dart_New(GLFWVersion_type, Dart_Null(), 3, arguments));
}

GLFWvidmode *NewGLFWvidmodeFromDart(Dart_Handle vidmode_handle) {
  GLFWvidmode *vidmode =
      reinterpret_cast<GLFWvidmode *>(malloc(sizeof(GLFWvidmode)));

  Dart_Handle width_obj =
      Dart_GetField(vidmode_handle, Dart_NewStringFromCString("width"));
  Dart_Handle height_obj =
      Dart_GetField(vidmode_handle, Dart_NewStringFromCString("height"));
  Dart_Handle redBits_obj =
      Dart_GetField(vidmode_handle, Dart_NewStringFromCString("redBits"));
  Dart_Handle greenBits_obj =
      Dart_GetField(vidmode_handle, Dart_NewStringFromCString("greenBits"));
  Dart_Handle blueBits_obj =
      Dart_GetField(vidmode_handle, Dart_NewStringFromCString("blueBits"));
  Dart_Handle refreshRate_obj =
      Dart_GetField(vidmode_handle, Dart_NewStringFromCString("refreshRate"));

  HandleError(Dart_IntegerToInt(width_obj, &(vidmode->width)));
  HandleError(Dart_IntegerToInt(height_obj, &(vidmode->height)));
  HandleError(Dart_IntegerToInt(redBits_obj, &(vidmode->redBits)));
  HandleError(Dart_IntegerToInt(greenBits_obj, &(vidmode->greenBits)));
  HandleError(Dart_IntegerToInt(blueBits_obj, &(vidmode->blueBits)));
  HandleError(Dart_IntegerToInt(refreshRate_obj, &(vidmode->refreshRate)));

  return vidmode;
}

GLFWgammaramp *NewGLFWgammarampFromDart(Dart_Handle gammaramp_handle) {
  GLFWgammaramp *gammaramp =
      reinterpret_cast<GLFWgammaramp *>(malloc(sizeof(GLFWgammaramp)));

  Dart_Handle red_obj =
      Dart_GetField(gammaramp_handle, Dart_NewStringFromCString("red"));
  Dart_Handle green_obj =
      Dart_GetField(gammaramp_handle, Dart_NewStringFromCString("green"));
  Dart_Handle blue_obj =
      Dart_GetField(gammaramp_handle, Dart_NewStringFromCString("blue"));
  Dart_Handle size_obj =
      Dart_GetField(gammaramp_handle, Dart_NewStringFromCString("size"));

  HandleError(Dart_IntegerToUInt(size_obj, &(gammaramp->size)));

  int size = gammaramp->size;

  gammaramp->red =  // NOLINTNEXTLINE
      reinterpret_cast<unsigned short *>(malloc(sizeof(unsigned short) * size));
  gammaramp->green =  // NOLINTNEXTLINE
      reinterpret_cast<unsigned short *>(malloc(sizeof(unsigned short) * size));
  gammaramp->blue =  // NOLINTNEXTLINE
      reinterpret_cast<unsigned short *>(malloc(sizeof(unsigned short) * size));

  for (int i = 0; i < size; i++) {
    Dart_Handle ri, gi, bi;
    ri = Dart_ListGetAt(red_obj, i);
    gi = Dart_ListGetAt(green_obj, i);
    bi = Dart_ListGetAt(blue_obj, i);

    HandleError(Dart_IntegerToUShort(ri, &(gammaramp->red[i])));
    HandleError(Dart_IntegerToUShort(gi, &(gammaramp->green[i])));
    HandleError(Dart_IntegerToUShort(bi, &(gammaramp->blue[i])));
  }

  return gammaramp;
}

GLFWimage *NewGLFWimageFromDart(Dart_Handle image_handle) {
  GLFWimage *image = reinterpret_cast<GLFWimage *>(malloc(sizeof(GLFWimage)));

  Dart_Handle width_obj =
      Dart_GetField(image_handle, Dart_NewStringFromCString("width"));
  Dart_Handle height_obj =
      Dart_GetField(image_handle, Dart_NewStringFromCString("height"));
  Dart_Handle pixels_obj =
      Dart_GetField(image_handle, Dart_NewStringFromCString("pixels"));

  HandleError(Dart_IntegerToInt(width_obj, &(image->width)));
  HandleError(Dart_IntegerToInt(height_obj, &(image->height)));

  int width = image->width;
  int height = image->height;

  image->pixels = reinterpret_cast<unsigned char *>(
      malloc(sizeof(unsigned char) * width * height * 4));

  for (int i = 0; i < width * height * 4; i++) {
    Dart_Handle pi = Dart_ListGetAt(pixels_obj, i);

    HandleError(Dart_IntegerToUChar(pi, &(image->pixels[i])));
  }

  return image;
}
