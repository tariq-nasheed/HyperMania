#pragma once

// im sorry jesus
typedef struct {
	int32 type; // -1 means untransformed
	Animator animator;
} HPZEmeraldExt;

struct {
	uint16 aniFrames;
	uint16 sfxSpecialWarp;
} HPZEmeraldStaticExt;

// left to right ordering converted to a centered origin that fans out with a left-leaning bias
uint32 super_emerald_lookup[7]    = { 5, 3, 1, 0, 2, 4, 6 }; // linear order -> super emerald order
uint32 super_emerald_revlookup[7] = { 3, 2, 4, 1, 5, 0, 6 }; // super emerald order -> linear order

// Sonic 3's emerald order is identical to Mania's with the exceptions being blue/purple and cyan/red are flipped
uint32 sonic3_emerald_lookup[7] = { 0, 1, 3, 2, 4, 6, 5 };

#include "Global/Debris.h"
#include "Global/HUD.h"
#include "Global/ImageTrail.h"
#include "Global/Player.h"
#include "Global/SpecialRing.h"
#include "LRZ/HPZEmerald.h"
#include "Menu/LevelSelect.h"
#include "Menu/UISaveSlot.h"
#include "MMZ/PlaneSeeSaw.h"
#include "UFO/SpecialClear.h"
#include "UFO/UFO_Player.h"
#include "UFO/UFO_Setup.h"
