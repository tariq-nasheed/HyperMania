#include "Kabasira.h"

ObjectKabasira *Kabasira;
void (*Kabasira_State_Moving)(void);

void Kabasira_EnemyInfoHook(void) {
	Mod.Super(Kabasira->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Kabasira->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Kabasira_State_Moving;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Kabasira->hitboxBadnik;
	++EnemyInfoSlot;
}
