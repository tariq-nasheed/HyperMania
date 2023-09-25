#!/bin/sh

modname="HyperMania"
logicname="hypermania"
filelist="Data mod.ini SETTINGS.md MANUAL.md src/release-files/modSettings.ini src/release-files/HyperManiaSaveData.bin src/release-files/Data/Game/GameConfig.bin"
releasedir="HyperMania"

BuildMods() {
	if [ ! -d build ]; then
		mkdir build
	fi
	cd build
	cmake $@ ../.. --fresh
	make -j8
	cd ../SHCLogo-RSDKv5Decomp
	if [ ! -d build ]; then
		mkdir build
	fi
	cd build
	cmake $@ .. --fresh
	make -j8
	cd ../..
}

if [ ! -d $releasedir ]; then
	mkdir $releasedir
fi

cd ..
cp -R --target-directory=src/$releasedir $filelist
cd src

# UP-TO-DATE MOD LOADER VERSIONS ###############################################
# linux
BuildMods
cp -R build/$logicname.so SHCLogo-RSDKv5Decomp/build/SHCLogo.so $releasedir
tar czf $modname-linux.tar.gz $releasedir
rm $releasedir/*.so
# windows
BuildMods -DCMAKE_SYSTEM_NAME=Windows
cp -R build/$logicname.dll SHCLogo-RSDKv5Decomp/build/SHCLogo.dll $releasedir
zip -r $modname-windows.zip $releasedir
rm $releasedir/*.dll

# LEGACY MOD LOADER VERSIONS ###################################################
cp -R release-files/Data $releasedir
# linux
BuildMods -DLEGACY=true
cp -R build/$logicname.so SHCLogo-RSDKv5Decomp/build/SHCLogo.so $releasedir
tar czf $modname-linux-legacy.tar.gz $releasedir
rm $releasedir/*.so
# windows
BuildMods -DCMAKE_SYSTEM_NAME=Windows -DLEGACY=true
cp -R build/$logicname.dll SHCLogo-RSDKv5Decomp/build/SHCLogo.dll $releasedir
zip -r $modname-windows-legacy.zip $releasedir
rm $releasedir/*.dll


# CLEANUP ######################################################################
echo "i'm too afraid to put rm here so CLEAN IT YOURSELF BUM"
