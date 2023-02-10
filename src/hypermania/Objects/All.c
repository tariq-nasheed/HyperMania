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
	int32 color; // -1 means untransformed
	Animator animator;
} HPZEmeraldExt;

uint32 super_emerald_lookup[7] = {
	7, // red
	3, // blue
	2, // yellow
	1, // green
	4, // purple
	5, // gray
	6  // cyan
};


#include "Player.c"
#include "ImageTrail.c"
#include "SpecialRing.c"
#include "UFO_Setup.c"
#include "UFO_Player.c"
#include "SpecialClear.c"
#include "HUD.c"
#include "UISaveSlot.c"

#include "SuperFlicky.c"
#include "HyperStars.c"

struct {
	uint16 aniFrames;
	uint16 sfxSpecialWarp;
} HPZEmeraldStaticExt;

#include "HPZ/HPZSetup.c"
#include "HPZ/HPZIntro.c"
#include "HPZ/HPZBeam.c"
#include "HPZ/HPZEmerald.c"

#include "Enemy.c"
