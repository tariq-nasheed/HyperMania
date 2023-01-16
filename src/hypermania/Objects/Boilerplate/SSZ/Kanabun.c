#include "Kanabun.h"

ObjectKanabun *Kanabun;
void (*Kanabun_State_Moving)(void);
void (*Kanabun_State_Turning)(void);

void Kanabun_EnemyInfoHook(void) {
	Mod.Super(Kanabun->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Kanabun->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Kanabun_State_Moving;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Kanabun->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Kanabun_State_Turning;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Kanabun->hitboxBadnik;
	++EnemyInfoSlot;
}
