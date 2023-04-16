#!/bin/sh

modname="HyperMania"
logicname="hypermania"
filelist="Data mod.ini"
srclist="LICENSE *.sh CMakeLists.txt hypermania GameAPI release-files"

if [ ! -d build ]; then
	mkdir build
fi

# UP-TO-DATE MOD LOADER VERSIONS ###############################################
# linux
cd build
cmake ..
make
cd ../..
tar czf src/$modname-linux.tar.gz $filelist -C src/release-files modSettings.ini -C ../build $logicname.so
cd src
# windows
cd build
cmake -DWINDOWS_BUILD=true ..
make
cd ../..
zip -r src/$modname-windows.zip $filelist
zip -r src/$modname-windows.zip --junk-paths src/release-files/modSettings.ini src/build/$logicname.dll
cd src

# LEGACY MOD LOADER VERSIONS ###################################################
# linux
cd build
cmake -DLEGACY=true ..
make
cd ../..
tar czf src/$modname-linux-legacy.tar.gz $filelist -C src/release-files Data modSettings.ini -C ../build $logicname.so
cd src
# windows
cd build
cmake -DLEGACY=true -DWINDOWS_BUILD=true ..
make
cd ../..
zip -r src/$modname-windows-legacy.zip $filelist
zip -r src/$modname-windows-legacy.zip --junk-paths src/release-files/modSettings.ini src/build/$logicname.dll
cd src/release-files
zip -r ../$modname-windows-legacy.zip Data
cd ..
