#include "TurboTurtle.h"

ObjectTurboTurtle *TurboTurtle;

void TurboTurtle_EnemyInfoHook(void) {
	Mod.Super(TurboTurtle->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = TurboTurtle->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &TurboTurtle->hitboxBadnik;
	++EnemyInfoSlot;
}
