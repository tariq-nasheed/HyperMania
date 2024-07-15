<h1 style="text-align: center;">HyperMania</h1>

![Alt text](images/icon.png?raw=true "icon")

![Alt text](images/1.png?raw=true "screenshot")

![Alt text](images/2.png?raw=true "screenshot")

![Alt text](images/3.png?raw=true "screenshot")

Sonic Mania decomp mod that adds Super Emeralds and Hyper forms into the game, features high degree of accuracy to S3&K with code based directly on [Sonic 3 AIR](https://github.com/Eukaryot/sonic3air).

***WIP***, contains some bugs here and there as well as some missing features. (Mainly a lack of new special stages with encore modes' being used as a substitute)

# Installation
The mod was developed for v5U and at the moment officially supports Windows, Linux and Android. Releases use the x64 instruction set for desktop platforms and AArch64 for Android, with desktop builds also coming in "legacy" variants for people still running 1.0.0 of the decomp.

Extract HyperMania into the `mods` folder of your decomp installation (create the folder if it doesn't exist), then enable it in the 'Mods' section of the developer menu.
(Follow [this guide](https://steamcommunity.com/sharedfiles/filedetails/?id=1123456515) if you don't know how to access it)

**For Android users:** you also need to take `libhypermania.so` out of the mods' folder and put it into `lib/arm64-v8a/` of your RSDKv5U apk. Make sure you have some way of opening or packing/unpacking apk files. (if you don't do this RSDKv5U can't find the logic file and you won't be able to play the mod)
# How to Build

## Unix-like
Initialize GameAPI with `git submodule update --init` then run these commands:

```
mkdir build
cd build
cmake .. .
make
mv hypermania.so ../../
```
You can use `./build.sh` in `src/` to automate this process if you don't mind running CMake every time you compile.

## Windows (Visual Studio)
- Make sure to have the "Desktop Development with C++" workload installed so you have access to CMake.
- When Visual Studio prompts you to enable CMake Integration, pick "Enable and set source directory" and select `CMakeLists.txt`.
- Build the project.
- move `hypermania.dll` from `out\build\(ARCHITECTURE)-Debug` to the mods' root directory (where `mod.ini` is).

## Android
See [RSDKv5-Decompilation/dependencies/android/README.md](https://github.com/RSDKModding/RSDKv5-Decompilation/blob/master/dependencies/android/README.md).

## CMake options
- `RELEASE` - Set to strip debug info from binary
- `LEGACY` - Set to use version 1 of the mod loader

# Planned features
+ Extra GFX/SFX
+ New special stages
+ New mechanic(s) for new special stages

# Credits
+ jubbalub + Hydropper - Super Emerald sprites, emerald cave map
+ Tee Lopes - Sonic Forces Theme Unofficial Remix (Hyper theme)
+ KiaraGale - Underwater Hyper palettes, inactive Super Emerald sprite, HPZ teleporter tiles
+ Braven - yellow + red super emerald palettes
+ Axanery - `GameConfig.bin`
