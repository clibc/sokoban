#!/bin/bash

CC="gcc"
files="./src/*.c"
flags="-g -O0 -Wall -std=c17"
includes="-I ./dependencies/ \
	  -I ./src/"
libs="-lGL -lglfw -lGLEW"

time $CC $flags $includes $files -lm $libs
