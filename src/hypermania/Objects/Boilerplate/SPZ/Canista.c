#include "Canista.h"

ObjectCanista *Canista;
void (*Canista_State_Moving)(void);
void (*Canista_State_Idle)(void);

void Canista_EnemyInfoHook(void) {
	Mod.Super(Canista->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Canista->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Canista_State_Moving;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Canista->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Canista_State_Idle;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Canista->hitboxBadnik;
	++EnemyInfoSlot;
}