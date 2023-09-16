#!/bin/sh

modname="HyperMania"
logicname="hypermania"
filelist="Data mod.ini SETTINGS.md MANUAL.md src/release-files/modSettings.ini"
releasedir="HyperMania"

if [ ! -d build ]; then
	mkdir build
fi

if [ ! -d $releasedir ]; then
	mkdir $releasedir
fi

cd ..
cp -R --target-directory=src/$releasedir $filelist
cd src

# UP-TO-DATE MOD LOADER VERSIONS ###############################################
# linux
cd build
cmake ../.. --fresh
make -j8
cd ..
cp -R build/$logicname.so $releasedir
tar czf $modname-linux.tar.gz $releasedir
rm $releasedir/$logicname.so
# windows
cd build
cmake -DCMAKE_SYSTEM_NAME=Windows ../.. --fresh
make -j8
cd ..
cp -R build/$logicname.dll $releasedir
zip -r $modname-windows.zip $releasedir
rm $releasedir/$logicname.dll

# LEGACY MOD LOADER VERSIONS ###################################################
cp -R release-files/Data $releasedir
# linux
cd build
cmake -DLEGACY=true ../.. --fresh
make -j8
cd ..
cp -R build/$logicname.so $releasedir
tar czf $modname-linux-legacy.tar.gz $releasedir
rm $releasedir/$logicname.so
# windows
cd build
cmake -DCMAKE_SYSTEM_NAME=Windows -DLEGACY=true ../.. --fresh
make -j8
cd ..
cp -R build/$logicname.dll $releasedir
zip -r $modname-windows-legacy.zip $releasedir
rm $releasedir/$logicname.dll


# CLEANUP ######################################################################
echo "i'm too afraid to put rm here so CLEAN IT YOURSELF BUM"
