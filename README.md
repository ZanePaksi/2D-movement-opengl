# 2D-movement-opengl

Using OpenGL and GLUT. Those will need to be installed prior to compiling.
Makefile to come soon, but until then compile with the following line

g++ movement_test.cpp -o test -lglut -lGLU -lGL


# Controls
ESC = Close window (Exit)

WASD:
  W/S = Move forward/backward
  A/D = rotate polygon counter-clockwise/clockwise

T = increment number of sides on polygon
