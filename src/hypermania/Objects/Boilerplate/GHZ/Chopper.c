#include "Chopper.h"

ObjectChopper *Chopper;
void (*Chopper_State_Jump)(void);
void (*Chopper_State_Swim)(void);
void (*Chopper_State_ChargeDelay)(void);

void Chopper_EnemyInfoHook(void) {
	Mod.Super(Chopper->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Chopper->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Chopper_State_Jump;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Chopper->hitboxJump;
	EnemyDefs[EnemyInfoSlot].states[1].func = Chopper_State_Swim;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Chopper->hitboxSwim;
	EnemyDefs[EnemyInfoSlot].states[2].func = Chopper_State_ChargeDelay;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Chopper->hitboxSwim;
	++EnemyInfoSlot;
}