#include "Woodrow.h"

ObjectWoodrow *Woodrow;
void (*Woodrow_State_Idle)(void);
void (*Woodrow_State_MoveUp)(void);
void (*Woodrow_State_MoveDown)(void);

void Woodrow_EnemyInfoHook(void) {
	Mod.Super(Woodrow->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Woodrow->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Woodrow_State_Idle;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Woodrow->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Woodrow_State_MoveUp;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Woodrow->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Woodrow_State_MoveDown;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Woodrow->hitboxBadnik;
	++EnemyInfoSlot;
}
