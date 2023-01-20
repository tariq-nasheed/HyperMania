# HyperMania
Sonic Mania decomp mod that adds Super Emeralds and Hyper forms into the game.
***Extremely WIP***, not really sutable for a full playthrough yet.
# Status
## Hyper abilities
Sonic and Knuckles are done. Tails is mostly done; super flickies only attack a partial amount of bosses.
## Emerald cave
Persistent data hasn't been implemented yet so giant rings always send you to the HPZ emerald cave. 
The cave itself is partly done but the transfer cutscene always plays and there's no results cutscene yet. Encore special stages are being used as a place holder until custom maps are created.
# Building
Compilation is pretty simple, just make sure to initialize the GameAPI submodule with `git submodule update --init` first then CMake should do the rest,  set `WINDOWS_BUILD` to true to enable cross-compiling to Windows.
`build.sh` is a simple shell script that automates the creation of a CMake build directory and runs make inside of it.
# Planned features
+ Hyper abilities for Mighty and Ray
+ Save game support
+ Extra GFX/SFX
+ New mechanic(s) for new special stages(?)
+ Config options (give everyone rainbow palettes, proto sparkles etc.)
+ mayyyybe an API for custom characters + enemies

# Credits
+ jubbalub + Hydropper - Super Emerald sprites, emerald cave map
+ Tee Lopes - Hyper theme
