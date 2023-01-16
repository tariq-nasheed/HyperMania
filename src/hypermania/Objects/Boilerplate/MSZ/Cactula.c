#include "Cactula.h"

ObjectCactula *Cactula;
void (*Cactula_State_CheckPlayerInRange)(void);
void (*Cactula_State_Rising)(void);
void (*Cactula_State_DropBomb)(void);

void Cactula_EnemyInfoHook(void) {
	Mod.Super(Cactula->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Cactula->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Cactula_State_CheckPlayerInRange;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Cactula->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Cactula_State_Rising;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Cactula->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Cactula_State_DropBomb;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Cactula->hitboxBadnik;
	++EnemyInfoSlot;
}
