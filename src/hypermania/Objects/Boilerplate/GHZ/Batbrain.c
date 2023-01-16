#include "Batbrain.h"

ObjectBatbrain *Batbrain;
void (*Batbrain_State_CheckPlayerInRange)(void);
void (*Batbrain_State_DropToPlayer)(void);
void (*Batbrain_State_Fly)(void);
void (*Batbrain_State_FlyToCeiling)(void);

void Batbrain_EnemyInfoHook(void) {
	Mod.Super(Batbrain->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Batbrain->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Batbrain_State_CheckPlayerInRange;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Batbrain->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Batbrain_State_DropToPlayer;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Batbrain->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Batbrain_State_Fly;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Batbrain->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = Batbrain_State_FlyToCeiling;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &Batbrain->hitboxBadnik;
	++EnemyInfoSlot;
}