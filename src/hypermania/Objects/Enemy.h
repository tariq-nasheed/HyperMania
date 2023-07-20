// WARNING: this file is heavily auto-generated, only modify if you know what you are doing
#include "GameAPI/Game.h"
// .h includes start on line 3
#include "Boilerplate/ERZ/PhantomMystic.h"
#include "Boilerplate/ERZ/PhantomShinobi.h"
#include "Boilerplate/ERZ/PhantomEgg.h"
#include "Boilerplate/TMZ/CrimsonEye.h"
#include "Boilerplate/MMZ/Gachapandora.h"
#include "Boilerplate/MMZ/EggPistonsMKII.h"
#include "Boilerplate/LRZ/RockDrill.h"
#include "Boilerplate/LRZ/HeavyKing.h"
#include "Boilerplate/LRZ/HeavyRider.h"
#include "Boilerplate/LRZ/DrillerdroidO.h"
#include "Boilerplate/LRZ/Drillerdroid.h"
#include "Boilerplate/OOZ/MegaOctus.h"
#include "Boilerplate/OOZ/MeterDroid.h"
#include "Boilerplate/MSZ/HeavyMystic.h"
#include "Boilerplate/MSZ/DBTower.h"
#include "Boilerplate/MSZ/UberCaterkiller.h"
#include "Boilerplate/HCZ/LaundroMobile.h"
#include "Boilerplate/SSZ/GigaMetal.h"
#include "Boilerplate/SSZ/MetalSonic.h"
#include "Boilerplate/SSZ/HotaruHiWatt.h"
#include "Boilerplate/PGZ/HeavyShinobi.h"
#include "Boilerplate/PGZ/Shiversaw.h"
#include "Boilerplate/FBZ/BigSqueeze.h"
#include "Boilerplate/SPZ/WeatherMobile.h"
#include "Boilerplate/CPZ/AmoebaDroid.h"
#include "Boilerplate/GHZ/DERobot.h"
#include "Boilerplate/GHZ/DDWrecker.h"


#include "Boilerplate/TMZ/FlasherMKII.h"
#include "Boilerplate/TMZ/TurboTurtle.h"
#include "Boilerplate/TMZ/SentryBug.h"
#include "Boilerplate/TMZ/BallHog.h"
#include "Boilerplate/MMZ/PohBee.h"
#include "Boilerplate/MMZ/Scarab.h"
#include "Boilerplate/MMZ/MechaBu.h"
#include "Boilerplate/LRZ/Fireworm.h"
#include "Boilerplate/LRZ/Rexon.h"
#include "Boilerplate/LRZ/Toxomister.h"
#include "Boilerplate/OOZ/Octus.h"
#include "Boilerplate/OOZ/Sol.h"
#include "Boilerplate/OOZ/Aquis.h"
#include "Boilerplate/MSZ/Rattlekiller.h"
#include "Boilerplate/MSZ/RollerMKII.h"
#include "Boilerplate/MSZ/Vultron.h"
#include "Boilerplate/MSZ/Bumpalo.h"
#include "Boilerplate/MSZ/Armadiloid.h"
#include "Boilerplate/MSZ/Cactula.h"
#include "Boilerplate/MSZ/Hatterkiller.h"
#include "Boilerplate/HCZ/TurboSpiker.h"
#include "Boilerplate/HCZ/Buggernaut.h"
#include "Boilerplate/HCZ/MegaChopper.h"
#include "Boilerplate/HCZ/Jawz.h"
#include "Boilerplate/HCZ/Jellygnite.h"
#include "Boilerplate/HCZ/Blastoid.h"
#include "Boilerplate/HCZ/Pointdexter.h"
#include "Boilerplate/SSZ/Kabasira.h"
#include "Boilerplate/SSZ/Dango.h"
#include "Boilerplate/SSZ/Kanabun.h"
#include "Boilerplate/SSZ/HotaruMKII.h"
#include "Boilerplate/SSZ/Hotaru.h"
#include "Boilerplate/PGZ/Woodrow.h"
#include "Boilerplate/PGZ/Dragonfly.h"
#include "Boilerplate/PGZ/IceBomba.h"
#include "Boilerplate/PGZ/JuggleSaw.h"
#include "Boilerplate/FBZ/FBZTrash.h"
#include "Boilerplate/FBZ/Technosqueek.h"
#include "Boilerplate/FBZ/Clucker.h"
#include "Boilerplate/FBZ/Blaster.h"
#include "Boilerplate/SPZ/Shutterbug.h"
#include "Boilerplate/SPZ/Canista.h"
#include "Boilerplate/SPZ/Tubinaut.h"
#include "Boilerplate/SPZ/MicDrop.h"
#include "Boilerplate/CPZ/Grabber.h"
#include "Boilerplate/CPZ/Spiny.h"
#include "Boilerplate/CPZ/CaterkillerJr.h"
#include "Boilerplate/CPZ/Bubbler.h"
#include "Boilerplate/GHZ/Splats.h"
#include "Boilerplate/GHZ/Newtron.h"
#include "Boilerplate/GHZ/Chopper.h"
#include "Boilerplate/GHZ/Crabmeat.h"
#include "Boilerplate/GHZ/Batbrain.h"
#include "Boilerplate/GHZ/Motobug.h"
#include "Boilerplate/GHZ/BuzzBomber.h"

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
} EntityEnemy;





extern int32 AttackableClasses_startidx;
bool32 Generic_CheckVulnerable(Entity* self);
Hitbox* Generic_GetHitbox(Entity* self);
void Generic_OnHit(EntityPlayer* player, Entity* self);
void Generic_BadnikBreak_NoEntity(EntityPlayer* player, Vector2 position, bool32 spawnAnimals);








typedef struct {
	uint16 classID;
	bool32 animal;
	bool32 boss;
	struct { void* func; Hitbox* hitbox; } states[8];
	bool32 (*check_func)(Entity*);
	Hitbox* (*hitbox_func)(Entity*);
	void (*destroy_func)(EntityPlayer*, Entity*); // NOTE -- destroy_func is used as the hit callback for bosses
} EnemyInfo;
extern EnemyInfo EnemyDefs[32];
extern int16 EnemyInfoSlot;

void Generic_BadnikBreak(EntityPlayer* player, Entity* entity, bool32 spawnAnimals);

#define GET_MANIA_FUNC(name) name = Mod.GetPublicFunction(NULL, #name)
#define REGISTER_ENEMY(name) MOD_REGISTER_OBJ_OVERLOAD(name, NULL, NULL, NULL, NULL, NULL, name##_EnemyInfoHook, NULL, NULL, NULL)

// object hooks start after the following line (pattern match)
#define HOOK_ENEMY_OBJECTS \
  OBJ_PHANTOMMYSTIC_SETUP; \
  OBJ_PHANTOMSHINOBI_SETUP; \
  OBJ_PHANTOMEGG_SETUP; \
  OBJ_CRIMSONEYE_SETUP; \
  OBJ_GACHAPANDORA_SETUP; \
  OBJ_EGGPISTONSMKII_SETUP; \
  OBJ_ROCKDRILL_SETUP; \
  OBJ_HEAVYKING_SETUP; \
  OBJ_HEAVYRIDER_SETUP; \
  OBJ_DRILLERDROIDO_SETUP; \
  OBJ_DRILLERDROID_SETUP; \
  OBJ_MEGAOCTUS_SETUP; \
  OBJ_METERDROID_SETUP; \
  OBJ_HEAVYMYSTIC_SETUP; \
  OBJ_DBTOWER_SETUP; \
  OBJ_UBERCATERKILLER_SETUP; \
  OBJ_LAUNDROMOBILE_SETUP; \
  OBJ_METALSONIC_SETUP; \
  OBJ_GIGAMETAL_SETUP; \
  OBJ_HOTARUHIWATT_SETUP; \
  OBJ_HEAVYSHINOBI_SETUP; \
  OBJ_SHIVERSAW_SETUP; \
  OBJ_BIGSQUEEZE_SETUP; \
  OBJ_WEATHERMOBILE_SETUP; \
  OBJ_AMOEBADROID_SETUP; \
  OBJ_DEROBOT_SETUP; \
  OBJ_DDWRECKER_SETUP; \
  \
  \
  REGISTER_ENEMY(FlasherMKII); \
  REGISTER_ENEMY(TurboTurtle); \
  REGISTER_ENEMY(SentryBug); \
  REGISTER_ENEMY(BallHog); \
  REGISTER_ENEMY(PohBee); \
  REGISTER_ENEMY(Scarab); \
  REGISTER_ENEMY(MechaBu); \
  REGISTER_ENEMY(Fireworm); \
  REGISTER_ENEMY(Rexon); \
  REGISTER_ENEMY(Toxomister); \
  REGISTER_ENEMY(Octus); \
  REGISTER_ENEMY(Sol); \
  REGISTER_ENEMY(Aquis); \
  REGISTER_ENEMY(Rattlekiller); \
  REGISTER_ENEMY(RollerMKII); \
  REGISTER_ENEMY(Vultron); \
  REGISTER_ENEMY(Bumpalo); \
  REGISTER_ENEMY(Armadiloid); \
  REGISTER_ENEMY(Cactula); \
  REGISTER_ENEMY(Hatterkiller); \
  REGISTER_ENEMY(TurboSpiker); \
  REGISTER_ENEMY(Buggernaut); \
  REGISTER_ENEMY(MegaChopper); \
  REGISTER_ENEMY(Jawz); \
  REGISTER_ENEMY(Jellygnite); \
  REGISTER_ENEMY(Blastoid); \
  REGISTER_ENEMY(Pointdexter); \
  OBJ_KABASIRA_SETUP; \
  OBJ_DANGO_SETUP; \
  OBJ_KANABUN_SETUP; \
  OBJ_HOTARUMKII_SETUP; \
  OBJ_HOTARU_SETUP; \
  OBJ_WOODROW_SETUP; \
  OBJ_DRAGONFLY_SETUP; \
  OBJ_ICEBOMBA_SETUP; \
  OBJ_JUGGLESAW_SETUP; \
  OBJ_FBZTRASH_SETUP; \
  OBJ_TECHNOSQUEEK_SETUP; \
  OBJ_CLUCKER_SETUP; \
  OBJ_BLASTER_SETUP; \
  OBJ_CANISTA_SETUP; \
  OBJ_TUBINAUT_SETUP; \
  OBJ_SHUTTERBUG_SETUP; \
  OBJ_MICDROP_SETUP; \
  OBJ_SPINY_SETUP; \
  OBJ_GRABBER_SETUP; \
  OBJ_CATERKILLERJR_SETUP; \
  OBJ_BUBBLER_SETUP; \
  OBJ_SPLATS_SETUP; \
  OBJ_NEWTRON_SETUP; \
  OBJ_CHOPPER_SETUP; \
  OBJ_CRABMEAT_SETUP; \
  OBJ_BATBRAIN_SETUP; \
  OBJ_MOTOBUG_SETUP; \
  OBJ_BUZZBOMBER_SETUP

// function imports start after the following line (pattern match
#define IMPORT_ENEMY_FUNCTIONS \
  GET_MANIA_FUNC(FlasherMKII_State_Idle); \
  GET_MANIA_FUNC(FlasherMKII_State_Moving); \
  GET_MANIA_FUNC(FlasherMKII_State_WeakFlash); \
  GET_MANIA_FUNC(FlasherMKII_State_StrongFlash); \
  GET_MANIA_FUNC(FlasherMKII_State_FinishedFlashing); \
  GET_MANIA_FUNC(SentryBug_State_ReturnToSlots); \
  GET_MANIA_FUNC(SentryBug_State_NetFlash); \
  GET_MANIA_FUNC(SentryBug_State_NetShrink); \
  GET_MANIA_FUNC(SentryBug_State_NetAppear); \
  GET_MANIA_FUNC(SentryBug_State_DropOrbs); \
  GET_MANIA_FUNC(SentryBug_State_AwaitPlayer); \
  GET_MANIA_FUNC(BallHog_State_DropBomb); \
  GET_MANIA_FUNC(BallHog_State_Land); \
  GET_MANIA_FUNC(BallHog_State_Jump); \
  GET_MANIA_FUNC(BallHog_State_Idle); \
  GET_MANIA_FUNC(MechaBu_State_Falling); \
  GET_MANIA_FUNC(MechaBu_State_Stopped); \
  GET_MANIA_FUNC(MechaBu_State_Moving); \
  GET_MANIA_FUNC(Fireworm_State_FlyAround); \
  GET_MANIA_FUNC(Rexon_State_Hidden); \
  GET_MANIA_FUNC(Rexon_State_Rising); \
  GET_MANIA_FUNC(Rexon_State_Shooting); \
  GET_MANIA_FUNC(Rexon_State_Destroyed); \
  GET_MANIA_FUNC(Rexon_State_Explode); \
  GET_MANIA_FUNC(Toxomister_State_CreateClouds); \
  GET_MANIA_FUNC(Octus_State_Fall); \
  GET_MANIA_FUNC(Octus_State_Shoot); \
  GET_MANIA_FUNC(Octus_State_Jump); \
  GET_MANIA_FUNC(Octus_State_JumpDelay); \
  GET_MANIA_FUNC(Octus_State_CheckPlayerInRange); \
  GET_MANIA_FUNC(Sol_State_ActiveFireball); \
  GET_MANIA_FUNC(Sol_State_NoOrbs); \
  GET_MANIA_FUNC(Sol_State_ShootingOrbs); \
  GET_MANIA_FUNC(Sol_State_Moving); \
  GET_MANIA_FUNC(Aquis_State_Flee); \
  GET_MANIA_FUNC(Aquis_State_Turning); \
  GET_MANIA_FUNC(Aquis_State_Shoot); \
  GET_MANIA_FUNC(Aquis_State_Moving); \
  GET_MANIA_FUNC(Aquis_State_Idle); \
  GET_MANIA_FUNC(RollerMKII_State_Idle); \
  GET_MANIA_FUNC(RollerMKII_State_SpinUp); \
  GET_MANIA_FUNC(Vultron_State_CheckPlayerInRange); \
  GET_MANIA_FUNC(Vultron_State_Hop); \
  GET_MANIA_FUNC(Vultron_State_Dive); \
  GET_MANIA_FUNC(Vultron_State_Flying); \
  GET_MANIA_FUNC(Vultron_State_Rise); \
  GET_MANIA_FUNC(Vultron_State_PrepareDive); \
  GET_MANIA_FUNC(Vultron_State_Targeting); \
  GET_MANIA_FUNC(Bumpalo_State_Falling); \
  GET_MANIA_FUNC(Bumpalo_State_Bumped); \
  GET_MANIA_FUNC(Bumpalo_State_Turning); \
  GET_MANIA_FUNC(Bumpalo_State_Charging); \
  GET_MANIA_FUNC(Bumpalo_State_Idle); \
  GET_MANIA_FUNC(Bumpalo_State_Moving); \
  GET_MANIA_FUNC(Armadiloid_State_Rider); \
  GET_MANIA_FUNC(Cactula_State_DropBomb); \
  GET_MANIA_FUNC(Cactula_State_Rising); \
  GET_MANIA_FUNC(Cactula_State_CheckPlayerInRange); \
  GET_MANIA_FUNC(TurboSpiker_State_FireShell); \
  GET_MANIA_FUNC(TurboSpiker_State_Falling); \
  GET_MANIA_FUNC(TurboSpiker_State_FinishTurning); \
  GET_MANIA_FUNC(TurboSpiker_State_Turning); \
  GET_MANIA_FUNC(TurboSpiker_State_Moving); \
  GET_MANIA_FUNC(TurboSpiker_State_Hidden); \
  GET_MANIA_FUNC(TurboSpiker_State_Idle); \
  GET_MANIA_FUNC(Buggernaut_State_FlyAway); \
  GET_MANIA_FUNC(Buggernaut_State_FlyTowardTarget); \
  GET_MANIA_FUNC(Buggernaut_State_Idle); \
  GET_MANIA_FUNC(MegaChopper_State_OutOfWater); \
  GET_MANIA_FUNC(MegaChopper_State_InWater); \
  GET_MANIA_FUNC(Jawz_State_Triggered); \
  GET_MANIA_FUNC(Jellygnite_State_Swimming); \
  GET_MANIA_FUNC(Jellygnite_State_GrabbedPlayer); \
  GET_MANIA_FUNC(Blastoid_State_Body); \
  GET_MANIA_FUNC(Pointdexter_State_Swimming)