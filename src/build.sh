#!/bin/sh

if [ ! -d build ]; then
	mkdir build
fi
cd build
cmake ../.. --fresh
make -j8
cp *.so ../..
cd ..
