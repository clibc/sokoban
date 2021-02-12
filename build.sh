#!/bin/bash

files="../src/*.c"
flags="-g -O0"
includes="-I ../dependencies/ \
	 -I ../src/"
libs="-lglfw -lGL"

pushd ./output/
time gcc $flags $includes $files $libs
popd

