#include "Crabmeat.h"

ObjectCrabmeat *Crabmeat;
void (*Crabmeat_State_Moving)(void);
void (*Crabmeat_State_Shoot)(void);

void Crabmeat_EnemyInfoHook(void) {
	Mod.Super(Crabmeat->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Crabmeat->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Crabmeat_State_Moving;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Crabmeat->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Crabmeat_State_Shoot;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Crabmeat->hitboxBadnik;
	++EnemyInfoSlot;
}