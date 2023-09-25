#!/bin/sh

if [ ! -d build ]; then
	mkdir build
fi
cd build
cmake ../.. --fresh
make -j8
cd ../SHCLogo-RSDKv5Decomp
if [ ! -d build ]; then
	mkdir build
fi
cd build
cmake .. --fresh
make -j8
mv SHCLogo.so ../../..
cd ../..
