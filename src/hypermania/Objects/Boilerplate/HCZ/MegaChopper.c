#include "MegaChopper.h"

ObjectMegaChopper *MegaChopper;
void (*MegaChopper_State_InWater)(void);
void (*MegaChopper_State_OutOfWater)(void);

void MegaChopper_EnemyInfoHook(void) {
	Mod.Super(MegaChopper->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = MegaChopper->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = MegaChopper_State_InWater;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &MegaChopper->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = MegaChopper_State_OutOfWater;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &MegaChopper->hitboxBadnik;
	++EnemyInfoSlot;
}
