#include "Pointdexter.h"

ObjectPointdexter *Pointdexter;
void (*Pointdexter_State_Swimming)(void);

void Pointdexter_EnemyInfoHook(void) {
	Mod.Super(Pointdexter->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Pointdexter->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Pointdexter_State_Swimming;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Pointdexter->hitbox;
	++EnemyInfoSlot;
}
