#!/bin/bash

files="../src/*.c"
flags="-g -O0"
includes="-I ../dependencies/ \
	  -I ../src/"
libs="-lglfw -lGL"

if [ ! -d "./output/" ]
then 
	mkdir ./output/
fi

pushd ./output/
time gcc $flags $includes $files -lm $libs
popd