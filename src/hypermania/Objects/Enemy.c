#include "Enemy.h"

#include "Boilerplate/ERZ/PhantomMystic.c"
#include "Boilerplate/ERZ/PhantomShinobi.c"
#include "Boilerplate/ERZ/PhantomEgg.c"
#include "Boilerplate/TMZ/CrimsonEye.c"
#include "Boilerplate/MMZ/Gachapandora.c"
#include "Boilerplate/MMZ/EggPistonsMKII.c"
#include "Boilerplate/LRZ/RockDrill.c"
#include "Boilerplate/LRZ/HeavyKing.c"
#include "Boilerplate/LRZ/HeavyRider.c"
#include "Boilerplate/LRZ/DrillerdroidO.c"
#include "Boilerplate/LRZ/Drillerdroid.c"
#include "Boilerplate/OOZ/MegaOctus.c"
#include "Boilerplate/OOZ/MeterDroid.c"
#include "Boilerplate/MSZ/HeavyMystic.c"
#include "Boilerplate/MSZ/DBTower.c"
#include "Boilerplate/MSZ/UberCaterkiller.c"
#include "Boilerplate/HCZ/LaundroMobile.c"
#include "Boilerplate/SSZ/GigaMetal.c"
#include "Boilerplate/SSZ/MetalSonic.c"
#include "Boilerplate/SSZ/HotaruHiWatt.c"
#include "Boilerplate/PGZ/HeavyShinobi.c"
#include "Boilerplate/PGZ/Shiversaw.c"
#include "Boilerplate/FBZ/BigSqueeze.c"
#include "Boilerplate/SPZ/WeatherMobile.c"
#include "Boilerplate/CPZ/AmoebaDroid.c"
#include "Boilerplate/GHZ/DERobot.c"
#include "Boilerplate/GHZ/DDWrecker.c"

#include "Boilerplate/TMZ/FlasherMKII.c"
#include "Boilerplate/TMZ/TurboTurtle.c"
#include "Boilerplate/TMZ/SentryBug.c"
#include "Boilerplate/TMZ/BallHog.c"
#include "Boilerplate/MMZ/PohBee.c"
#include "Boilerplate/MMZ/Scarab.c"
#include "Boilerplate/MMZ/MechaBu.c"
#include "Boilerplate/LRZ/Fireworm.c"
#include "Boilerplate/LRZ/Rexon.c"
#include "Boilerplate/LRZ/Toxomister.c"
#include "Boilerplate/OOZ/Octus.c"
#include "Boilerplate/OOZ/Sol.c"
#include "Boilerplate/OOZ/Aquis.c"
#include "Boilerplate/MSZ/Rattlekiller.c"
#include "Boilerplate/MSZ/RollerMKII.c"
#include "Boilerplate/MSZ/Vultron.c"
#include "Boilerplate/MSZ/Bumpalo.c"
#include "Boilerplate/MSZ/Armadiloid.c"
#include "Boilerplate/MSZ/Cactula.c"
#include "Boilerplate/MSZ/Hatterkiller.c"
#include "Boilerplate/HCZ/TurboSpiker.c"
#include "Boilerplate/HCZ/Buggernaut.c"
#include "Boilerplate/HCZ/MegaChopper.c"
#include "Boilerplate/HCZ/Jawz.c"
#include "Boilerplate/HCZ/Jellygnite.c"
#include "Boilerplate/HCZ/Blastoid.c"
#include "Boilerplate/HCZ/Pointdexter.c"
#include "Boilerplate/SSZ/Kabasira.c"
#include "Boilerplate/SSZ/Dango.c"
#include "Boilerplate/SSZ/Kanabun.c"
#include "Boilerplate/SSZ/HotaruMKII.c"
#include "Boilerplate/SSZ/Hotaru.c"
#include "Boilerplate/PGZ/Woodrow.c"
#include "Boilerplate/PGZ/Dragonfly.c"
#include "Boilerplate/PGZ/IceBomba.c"
#include "Boilerplate/PGZ/JuggleSaw.c"
#include "Boilerplate/FBZ/FBZTrash.c"
#include "Boilerplate/FBZ/Technosqueek.c"
#include "Boilerplate/FBZ/Clucker.c"
#include "Boilerplate/FBZ/Blaster.c"
#include "Boilerplate/SPZ/Shutterbug.c"
#include "Boilerplate/SPZ/Canista.c"
#include "Boilerplate/SPZ/Tubinaut.c"
#include "Boilerplate/SPZ/MicDrop.c"
#include "Boilerplate/CPZ/Grabber.c"
#include "Boilerplate/CPZ/Spiny.c"
#include "Boilerplate/CPZ/CaterkillerJr.c"
#include "Boilerplate/CPZ/Bubbler.c"
#include "Boilerplate/GHZ/Splats.c"
#include "Boilerplate/GHZ/Newtron.c"
#include "Boilerplate/GHZ/Chopper.c"
#include "Boilerplate/GHZ/Crabmeat.c"
#include "Boilerplate/GHZ/Batbrain.c"
#include "Boilerplate/GHZ/Motobug.c"
#include "Boilerplate/GHZ/BuzzBomber.c"