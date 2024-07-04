<h1 style="text-align: center;">HyperMania</h1>

![Alt text](images/icon.png?raw=true "icon")

![Alt text](images/1.png?raw=true "screenshot")

![Alt text](images/2.png?raw=true "screenshot")

![Alt text](images/3.png?raw=true "screenshot")

Sonic Mania decomp mod that adds Super Emeralds and Hyper forms into the game, features high degree of accuracy to S3&K with code based directly on [Sonic 3 AIR](https://github.com/Eukaryot/sonic3air).

***Extremely WIP***, casual play is possible but with bugs and rough presentation.

Press transform + up in debug mode while super or collect all Super Emeralds to transform into your Hyper form.
# Status
- Hyper abilities - All 5 characters have hyper abilities, Mighty's and Ray's are kinda buggy and need some extra work.
- Hidden Palace Zone - Can be accessed when touching a Super Ring with all Chaos Emeralds collected, features transfer animation and ability to collect Super Emeralds.
Encore special stages are being used as placeholders until new maps are created.

# How to build

## Unix-like
Initialize GameAPI with `git submodule update --init` then run these commands

```
mkdir build
cd build
cmake .. .
make
mv hypermania.so ../../
```
or you can use `./build.sh` in `src/` to automate this process if you don't mind running CMake every time you compile

## Windows (Visual Studio)
- Make sure to have the "Desktop Development with C++" workload installed so you have access to CMake
- When Visual Studio prompts you to enable CMake Integration, pick "Enable and set source directory" and select `CMakeLists.txt`
- Build the project
- move `hypermania.dll` from `out\build\(ARCHITECTURE)-Debug` to the mods' root directory (where `mod.ini` is)

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
