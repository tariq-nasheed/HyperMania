#include "FlasherMKII.h"

ObjectFlasherMKII *FlasherMKII;
void (*FlasherMKII_State_Idle)(void);
void (*FlasherMKII_State_Moving)(void);
void (*FlasherMKII_State_WeakFlash)(void);
void (*FlasherMKII_State_StrongFlash)(void);
void (*FlasherMKII_State_FinishedFlashing)(void);

// again, like Vultron uses frame dimensions
Hitbox hitbox;

void FlasherMKII_EnemyInfoHook(void) {
	hitbox.left   = -24;
	hitbox.top    = -24;
	hitbox.right  = 24;
	hitbox.bottom = -24;
	Mod.Super(FlasherMKII->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = FlasherMKII->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = FlasherMKII_State_Idle;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &hitbox;
	EnemyDefs[EnemyInfoSlot].states[1].func = FlasherMKII_State_Moving;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &hitbox;
	EnemyDefs[EnemyInfoSlot].states[2].func = FlasherMKII_State_WeakFlash;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &hitbox;
	EnemyDefs[EnemyInfoSlot].states[3].func = FlasherMKII_State_StrongFlash;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &hitbox;
	EnemyDefs[EnemyInfoSlot].states[4].func = FlasherMKII_State_FinishedFlashing;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &hitbox;
	EnemyDefs[EnemyInfoSlot].destroy_func = FlasherMKII_StopSound;
	++EnemyInfoSlot;
}

void FlasherMKII_StopSound(EntityPlayer* player, Entity* e) {
	EntityFlasherMKII* self = (EntityFlasherMKII*)e;
	RSDK.StopSfx(FlasherMKII->sfxZap);
	BreakBadnik(player, e);
}