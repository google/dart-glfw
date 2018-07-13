# Dart bindings to [GLFW](http://glfw.org/) 3.2.1.

Supports Linux and Windows. OSX is not supported due to inherent
incompatibilites in the OSX UI threading model, as well as Apple announcing the
discontinuing of support of OpenGL on OSX (https://goo.gl/qQdeQ5).

# Steps to generate the bindings

```shell
mkdir -p lib/src/generated/
pub run tools/glfw_generator.dart --glfw3_path=<path to glfw3.h>
clang-format -i --style=Google generated/*.{cc,h}
dartfmt -w generated/*.dart
mv generated/* lib/src/generated
```

# Steps to compile the bindings

The previous method for compiling the bindings is no longer available. We are
working on a new solution for both Linux and Windows.

In the meantime, the Makefile in the lib/ directory is a good starting point for
compiling on Linux.

# Notes about the auto-generated bindings

-   `glfwWindowShouldClose` returns an `int`, rather than a `bool`, but unlike
    in C, the expression `!(1)` returns true so you must explicitly test
    `glfwWindowShouldClose(window) != 1`
    -   There is also a convenience function \
        `bool glfwWindowShouldCloseAsBool(GLFWwindow window)`

# The following functions have changed from the C GLFW API

These changes are due to the C library's use of pointer arguments to return
values. See also lib/src/manual\_bindings.dart.

-   glfwGetVersion
    -   Returns a `GLFWVersion` instance which has `major`, `minor`, `rev`
        fields.
-   glfwGetMonitors
    -   Returns a `List<GLFWmonitor>` instance.
-   glfwGetMonitorPos
    -   Returns a `Point` instance.
-   glfwGetMonitorPhysicalSize
    -   Returns a `Rectangle` instance with `xpos` and `ypos` set to 0.
-   glfwGetVideoModes
    -   Returns a `List<GLFWvidmode>` instance.
-   glfwGetWindowPos
    -   Returns a `Point` instance.
-   glfwGetWindowSize
    -   Returns a `Rectangle` instance with `xpos` and `ypos` set to 0.
-   glfwGetFramebufferSize
    -   Returns a `Rectangle` instance with `xpos` and `ypos` set to 0.
-   glfwGetWindowFrameSize
    -   Returns a `Rectangle` instance.
-   glfwSetWindowUserPointer
    -   `pointer` parameter is a Dart `Object`.
-   glfwGetWindowUserPointer
    -   Returns an `Object` instance.
-   glfwGetCursorPos
    -   Returns a `Point` instance.
-   glfwGetJoystickAxes
    -   Returns a `List<double>` instance.
-   glfwGetJoystickButtons
    -   Returns a `List<int>` instance.

# The following functions are additions to the C GLFW API

-   glfwSwapBuffersAsync
    -   An async version of glfwSwapBuffers that can be `await`-ed. This avoids
        blocking the current isolate while the glfwSwapBuffers call is waiting
        to finish.
