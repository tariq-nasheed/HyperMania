#include "Dango.h"

ObjectDango *Dango;
void (*Dango_State_Walking)(void);
void (*Dango_State_Turning)(void);
void (*Dango_State_Falling_Uncurled)(void);
void (*Dango_State_Curling)(void);
void (*Dango_State_Rolling)(void);
void (*Dango_State_Falling_Curled)(void);
void (*Dango_State_Uncurling)(void);

void Dango_EnemyInfoHook(void) {
	Mod.Super(Dango->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Dango->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Dango_State_Walking;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Dango->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Dango_State_Turning;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Dango->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Dango_State_Falling_Uncurled;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Dango->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = Dango_State_Curling;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &Dango->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[4].func = Dango_State_Rolling;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &Dango->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[5].func = Dango_State_Falling_Curled;
	EnemyDefs[EnemyInfoSlot].states[5].hitbox = &Dango->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[6].func = Dango_State_Uncurling;
	EnemyDefs[EnemyInfoSlot].states[6].hitbox = &Dango->hitboxBadnik;
	++EnemyInfoSlot;
}
