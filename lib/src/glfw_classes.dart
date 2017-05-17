// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

part of glfw;

/// An opaque pointer to a GLFW object.
abstract class GLFWpointer {
  int get _native_pointer;
}

/// A GLFWpointer implementation representing a monitor.
class GLFWmonitor implements GLFWpointer {
  final int _native_pointer;
  GLFWmonitor(this._native_pointer);
  String toString() => "GLFWmonitor(0x${_native_pointer.toRadixString(16)})";
}

/// A GLFWpointer implementation representing a window.
class GLFWwindow {
  final int _native_pointer;
  GLFWwindow(this._native_pointer);
  String toString() => "GLFWwindow(0x${_native_pointer.toRadixString(16)})";
}

/// A GLFWpointer implementation representing a cursor.
class GLFWcursor {
  final int _native_pointer;
  GLFWcursor(this._native_pointer);
  String toString() => "GLFWcursor(0x${_native_pointer.toRadixString(16)})";
}

/// A class mirroring the `GLFWvidmode` struct defined in `<GLFW/glfw3.h>`
/// See the official
/// [GLFWvidmode documentation](http://www.glfw.org/docs/latest/structGLFWvidmode.html)
/// for more information.
class GLFWvidmode {
  int width;
  int height;
  int redBits;
  int greenBits;
  int blueBits;
  int refreshRate;
  GLFWvidmode(this.width, this.height, this.redBits, this.greenBits,
      this.blueBits, this.refreshRate);
}

/// A class mirroring the `GLFWgammaramp` struct defined in `<GLFW/glfw3.h>`
/// See the official
/// [GLFWgammaramp documentation](http://www.glfw.org/docs/latest/structGLFWgammaramp.html)
/// for more information.
class GLFWgammaramp {
  List<int> red;
  List<int> green;
  List<int> blue;
  int size;
  GLFWgammaramp(this.red, this.green, this.blue, this.size);
}

/// A class mirroring the `GLFWimage` struct defined in `<GLFW/glfw3.h>`
/// See the official
/// [GLFWimage documentation](http://www.glfw.org/docs/latest/structGLFWimage.html)
/// for more information.
class GLFWimage {
  int width;
  int height;

  /// A list of pixel color values in RGBA format
  List<int> pixels;
  GLFWimage(this.width, this.height, this.pixels);
}
