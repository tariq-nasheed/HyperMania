#include "Scarab.h"

ObjectScarab *Scarab;

void Scarab_EnemyInfoHook(void) {
	Mod.Super(Scarab->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Scarab->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Scarab->hitboxBadnik;
	++EnemyInfoSlot;
}
