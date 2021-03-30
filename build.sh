#!/bin/bash

CC="gcc"
files="./src/*.c"
flags="-g -O0 -Wall -Wextra -std=c17 -pedantic"
includes="-I ./dependencies/ \
	  -I ./src/"
libs="-lGL -lglfw -lGLEW"

time $CC $flags $includes $files -lm $libs
