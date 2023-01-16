#include "Octus.h"

ObjectOctus *Octus;
void (*Octus_State_CheckPlayerInRange)(void);
void (*Octus_State_JumpDelay)(void);
void (*Octus_State_Jump)(void);
void (*Octus_State_Shoot)(void);
void (*Octus_State_Fall)(void);

void Octus_EnemyInfoHook(void) {
	Mod.Super(Octus->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Octus->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Octus_State_CheckPlayerInRange;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Octus->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Octus_State_JumpDelay;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Octus->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Octus_State_Jump;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Octus->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = Octus_State_Shoot;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &Octus->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[4].func = Octus_State_Fall;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &Octus->hitboxBadnik;
	++EnemyInfoSlot;
}
