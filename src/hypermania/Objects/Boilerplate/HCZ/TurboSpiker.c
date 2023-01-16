#include "TurboSpiker.h"

ObjectTurboSpiker *TurboSpiker;
void (*TurboSpiker_State_Idle)(void);
void (*TurboSpiker_State_Hidden)(void);
void (*TurboSpiker_State_Moving)(void);
void (*TurboSpiker_State_Turning)(void);
void (*TurboSpiker_State_FinishTurning)(void);
void (*TurboSpiker_State_Falling)(void);
void (*TurboSpiker_State_FireShell)(void);

void TurboSpiker_EnemyInfoHook(void) {
	Mod.Super(TurboSpiker->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = TurboSpiker->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = TurboSpiker_State_Idle;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &TurboSpiker->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = TurboSpiker_State_Hidden;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &TurboSpiker->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = TurboSpiker_State_Moving;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &TurboSpiker->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = TurboSpiker_State_Turning;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &TurboSpiker->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[4].func = TurboSpiker_State_FinishTurning;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &TurboSpiker->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[5].func = TurboSpiker_State_Falling;
	EnemyDefs[EnemyInfoSlot].states[5].hitbox = &TurboSpiker->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[6].func = TurboSpiker_State_FireShell;
	EnemyDefs[EnemyInfoSlot].states[6].hitbox = &TurboSpiker->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].destroy_func = TurboSpiker_DestroySpike;
	++EnemyInfoSlot;
}

void TurboSpiker_DestroySpike(EntityPlayer* player, Entity* e) {
	EntityTurboSpiker* self = (EntityTurboSpiker*)e;
	if (self->spike) destroyEntity(self->spike);
	BreakBadnik(player, e);
}