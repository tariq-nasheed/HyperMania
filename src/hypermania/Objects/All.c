#include "util.h"
#include "Boilerplate/SaveGame.c"
#include "Boilerplate/Animals.c"
#include "Boilerplate/Camera.c"
#include "Boilerplate/CollapsingPlatform.c"
#include "Boilerplate/Debris.c"
#include "Boilerplate/Explosion.c"
#include "Boilerplate/FXFade.c"
#include "Boilerplate/Ring.c"
#include "Boilerplate/ScoreBonus.c"
#include "Boilerplate/ItemBox.c"
#include "Boilerplate/Zone.c"
#include "Boilerplate/Music.c"
#include "Boilerplate/Global/PauseMenu.c"

#include "Boilerplate/CPZ/CPZSetup.c"
#include "Boilerplate/OOZ/OOZSetup.c"
#include "Boilerplate/HCZ/HCZSetup.c"
#include "Boilerplate/MMZ/FarPlane.c"
#include "Boilerplate/ERZ/ERZStart.c"
#include "Boilerplate/BSS/BSS_Setup.c"

// im sorry jesus
typedef struct {
	Entity* owner;
	int32 type; // -1 means untransformed
	Animator animator;
} HPZEmeraldExt;

// left to right ordering converted to a centered origin that fans out with a left-leaning bias
uint32 super_emerald_lookup[7]    = { 5, 3, 1, 0, 2, 4, 6 }; // linear order -> super emerald order
uint32 super_emerald_revlookup[7] = { 3, 2, 4, 1, 5, 0, 6 }; // super emerald order -> linear order

// Sonic 3's emerald order is identical to Mania's with the exceptions being blue/purple and cyan/red are flipped
uint32 sonic3_emerald_lookup[7] = { 0, 1, 3, 2, 4, 6, 5 };


#include "Player.c"
#include "ImageTrail.c"
#include "SpecialRing.c"
#include "UFO_Setup.c"
#include "UFO_Player.c"
#include "HUD.c"
#include "UISaveSlot.c"
#include "PlaneSeeSaw.c"

#include "SuperFlicky.c"
#include "HyperStars.c"
#include "JetGlideEffect.c"

struct {
	uint16 aniFrames;
	uint16 sfxSpecialWarp;
} HPZEmeraldStaticExt;

#include "HPZ/HPZSetup.c"
#include "HPZ/HPZIntro.c"
#include "HPZ/HPZBeam.c"
#include "HPZ/HPZEmerald.c"
#include "SpecialClear.c"

#include "Enemy.c"
