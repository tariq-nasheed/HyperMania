#include "RollerMKII.h"

ObjectRollerMKII *RollerMKII;
void (*RollerMKII_State_Idle)(void);
void (*RollerMKII_State_SpinUp)(void);

void RollerMKII_EnemyInfoHook(void) {
	Mod.Super(RollerMKII->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = RollerMKII->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = RollerMKII_State_Idle;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &RollerMKII->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = RollerMKII_State_SpinUp;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &RollerMKII->hitboxBadnik;
	++EnemyInfoSlot;
}
