#!/bin/bash

files="../src/*.c"
flags="-g -O0 -Wno-implicit-function-declaration"
includes="-I ../dependencies/ \
	  -I ../src/"
libs="-lGL -lglfw"

if [ ! -d "./output/" ]
then 
	mkdir ./output/
fi

pushd ./output/
time gcc $flags $includes $files -lm $libs
popd
