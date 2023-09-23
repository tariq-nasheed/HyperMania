#ifndef HYPERMANIAVARIABLES_H
#define HYPERMANIAVARIABLES_H

#include "Mania/All.h"
#include "GameAPI/Game.h"

// =============================================================================

// Helper macros ---------------------------------------------------------------

// =============================================================================
#if RETRO_REV02
  #define MOD_PRINT(mode, msg, ...) RSDK.PrintLog(mode, "[%s] "msg, modID, __VA_ARGS__);
#else
  #define MOD_PRINT(mode, msg, ...) { \
    char str[512]; \
    sprintf(str, "[%s] "msg, modID, __VA_ARGS__); \
    RSDK.PrintMessage(str, MESSAGE_STRING); \
  }
#endif

#define IMPORT_PUBLIC_FUNC(name) { \
  name = Mod.GetPublicFunction(NULL, #name); \
  if (name == NULL) MOD_PRINT(PRINT_ERROR, #name" is not a public function\n", ""); \
}
#define HOOK_STATE(name, priority) { \
  void (*name##_fn) = Mod.GetPublicFunction(NULL, #name); \
  if (name##_fn == NULL) MOD_PRINT(PRINT_ERROR, #name" is not a public function\n", "") \
  else Mod.RegisterStateHook(name##_fn, name##_HOOK, priority); \
}
#define HOOK_IMPORTED_STATE(name, priority) Mod.RegisterStateHook(name, name##_HOOK, priority)

// =============================================================================

// Attackable Classes ----------------------------------------------------------

// =============================================================================
#define MAX_ATTACKABLE_CLASSES 64
#define ENTATTACK_INVALID -1

enum AttackableFlags {
	ATKFLAG_NONE     = 0x00,
	ATKFLAG_NOANIMAL = 0x01,
	ATKFLAG_ISBOSS   = 0x02
};

typedef struct {
	bool32  (*checkVulnerable)(Entity*);
	Hitbox* (*getHitbox)(Entity*);
	void    (*onHit)(EntityPlayer*, Entity*);
	void    (*adjustPos)(Entity*); // optional for "weird" classes (i.e. catterkiller jr.)
	uint8 flags;
} attackinfo_t;

// =============================================================================

// Misc. + Globals -------------------------------------------------------------

// =============================================================================
typedef struct {
	size_t size;
	void* mem;
} extmem_t;

typedef struct {
	int32 startIndex, endIndex;
	int32 rows;
	color* colors[6];
} hyperpal_t;

typedef struct {
	int32 hyperStyle; /* 0 - rainbow sonic, brighter super palettes for everyone else
	                     1 - rainbow sonic, super palettes + no hyper sparkles for everyone else
	                     2 - rainbow for all characters */
	bool32 hyperFlashDropDash; // set to true to activate drop dash instantly when using hyper flash
	bool32 hyperFlashForwarding; // set to true to treat no directional input as pressing forward when using hyper flash
	bool32 GSWburst; // set to true to enable gliding shock wave attacks' momentum addition qualities (also enables shockwave effect when starting glide)
	bool32 GSWitemBoxes; // set to true to enable GSW item box breaking capabilities (can be really annoying in encore mode)
	bool32 JEAjank; // set to enable old shitty Jackhammer Earthquake Attack physics seen in alpha builds
	float screenFlashFactor; // set to control intensity of screen flashes, with 1.0 being full intensity and 0.0 disabling flashes
	bool32 twoHeavensMode; // set to true to enable "Two Heavens mode" letting you choose between turning super OR hyper with the latter form consuming rings at a faster rate
	bool32 enableHyperMusic; // set to true to enable hyper music (duhhh!!!!!)
} HM_Config;

typedef struct {
	uint8 transferedEmeralds;
	uint8 padding1[3];
	uint8 superEmeralds;
	uint8 padding2[3];
} HM_SaveRAM;

typedef struct {
	// config
	HM_Config config;
	// save game stuff
	HM_SaveRAM  saveRAM[11];
	HM_SaveRAM  noSaveSlot;
	HM_SaveRAM* currentSave;
	// attackable classes system
	attackinfo_t AttackableClasses[MAX_ATTACKABLE_CLASSES];
	uint32       AttackableClasses_size;
	int32        AttackableClasses_startidx;
} HM_global_t;

extern HM_global_t* HM_globals;

#endif //! HYPERMANIAVARIABLES_H
