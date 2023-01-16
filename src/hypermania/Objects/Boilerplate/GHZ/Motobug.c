#include "Motobug.h"

ObjectMotobug *Motobug;
void (*Motobug_State_Fall)(void);
void (*Motobug_State_Move)(void);
void (*Motobug_State_Idle)(void);

void Motobug_EnemyInfoHook(void) {
	Mod.Super(Motobug->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Motobug->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Motobug_State_Fall;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Motobug->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Motobug_State_Move;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Motobug->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Motobug_State_Idle;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Motobug->hitboxBadnik;
	++EnemyInfoSlot;
}