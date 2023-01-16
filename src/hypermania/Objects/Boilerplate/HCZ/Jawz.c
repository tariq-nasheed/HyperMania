#include "Jawz.h"

ObjectJawz *Jawz;
void (*Jawz_State_Triggered)(void);

void Jawz_EnemyInfoHook(void) {
	Mod.Super(Jawz->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Jawz->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Jawz_State_Triggered;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Jawz->hitboxBadnik;
	++EnemyInfoSlot;
}
