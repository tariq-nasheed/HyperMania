#include "Buggernaut.h"

ObjectBuggernaut *Buggernaut;
void (*Buggernaut_State_Idle)(void);
void (*Buggernaut_State_FlyTowardTarget)(void);
void (*Buggernaut_State_FlyAway)(void);

void Buggernaut_EnemyInfoHook(void) {
	Mod.Super(Buggernaut->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Buggernaut->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Buggernaut_State_Idle;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Buggernaut->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Buggernaut_State_FlyTowardTarget;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Buggernaut->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Buggernaut_State_FlyAway;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Buggernaut->hitboxBadnik;
	++EnemyInfoSlot;
}
