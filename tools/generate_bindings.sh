#!/bin/bash
[ -d generated ] || mkdir generated/
python glfw_generator.py $1
clang-format -i -style=Google generated/*.{cc,h}
dartfmt -w generated/*.dart
