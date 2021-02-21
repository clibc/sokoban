#!/bin/bash

files="../src/*.c"
flags="-g -O0 -Wno-incompatible-pointer-types"
includes="-I ../dependencies/ \
	  -I ../src/"
libs="-lGL -lglfw -lGLEW"

if [ ! -d "./output/" ]
then 
	mkdir ./output/
fi

pushd ./output/
time gcc $flags $includes $files -lm $libs
popd
