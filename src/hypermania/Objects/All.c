#include "ModFunctions.h"

#include "Mania/Global/SaveGame.c"
#include "Mania/Global/Animals.c"
#include "Mania/Global/Camera.c"
#include "Mania/Common/CollapsingPlatform.c"
#include "Mania/Global/Explosion.c"
#include "Mania/Cutscene/FXFade.c"
#include "Mania/Global/Ring.c"
#include "Mania/Global/ScoreBonus.c"
#include "Mania/Global/ItemBox.c"
#include "Mania/Global/Zone.c"
#include "Mania/Global/Music.c"
#include "Mania/Global/PauseMenu.c"
#include "Mania/Global/InvincibleStars.c"

#include "Mania/CPZ/CPZSetup.c"
#include "Mania/OOZ/OOZSetup.c"
#include "Mania/HCZ/HCZSetup.c"
#include "Mania/MMZ/FarPlane.c"
#include "Mania/ERZ/ERZStart.c"
#include "Mania/BSS/BSS_Setup.c"

// im sorry jesus
typedef struct {
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
#include "LevelSelect.c"
#include "PlaneSeeSaw.c"
#include "Debris.c"

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
