#!/bin/sh

if [ "$1" = "shc" ]; then
	withSHC=true
fi
modname="HyperMania"
logicname="hypermania"
filelist="Data mod.ini MANUAL.md src/release-files/modSettings.ini src/release-files/HyperManiaSaveData.bin src/release-files/Data/Game/Game.xml"
releasedir="HyperMania"

if [ -n "$withSHC" ]; then
	echo "[SHC LOGO ENABLED]"
fi

BuildMods() {
	if [ ! -d build ]; then
		mkdir build
	fi

	args=$@
	if [ -n "$withSHC" ]; then
		args="$args -DSHCLOGO=true"
	fi

	cd build
	cmake $args ../.. --fresh
	make -j8
	cd ..
}

CopyLogicFiles() {
	copylist="build/$logicname.$1"
	if [ -n "$withSHC" ]; then
		copylist="$copylist build/SHCLogo.$1"
	fi
	cp $copylist $releasedir
}

if [ ! -d $releasedir ]; then
	mkdir $releasedir
fi

cd ..
cp -R --target-directory=src/$releasedir $filelist
if [ -n "$withSHC" ]; then
	rm src/$releasedir/mod.ini
	cp src/release-files/SHCmod.ini src/$releasedir
	mv src/$releasedir/SHCmod.ini src/$releasedir/mod.ini
	cp -R src/release-files/Logos src/$releasedir/Data/Stages
fi
cd src

# linux
BuildMods
CopyLogicFiles so
tar czf $modname-linux.tar.gz $releasedir
rm $releasedir/*.so
# windows
BuildMods -DCMAKE_SYSTEM_NAME=Windows
CopyLogicFiles dll
zip -r $modname-windows.zip $releasedir
rm $releasedir/*.dll

# CLEANUP ######################################################################
echo "\033[1;33mrelease builds done! removing temporary directory \"$releasedir\"...\033[0m"
rm -r $releasedir
