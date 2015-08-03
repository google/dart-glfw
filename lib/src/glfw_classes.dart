// Copyright (c) 2015, the Dart GLFW extension authors. All rights reserved.
// Please see the AUTHORS file for details. Use of this source code is governed
// by a BSD-style license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

part of glfw;

/// An opaque GLFW object representing a monitor.
class GLFWmonitor extends OpaquePointer {
  GLFWmonitor();
}

/// An opaque GLFW object representing a window.
class GLFWwindow extends OpaquePointer {
  GLFWwindow();
}

/// An opaque GLFW object representing a cursor.
class GLFWcursor extends OpaquePointer {
  GLFWcursor();
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
