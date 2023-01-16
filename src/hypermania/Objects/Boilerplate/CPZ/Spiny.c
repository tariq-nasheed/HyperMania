#include "Spiny.h"

ObjectSpiny *Spiny;
void (*Spiny_State_Floor)(void);
void (*Spiny_State_Shoot_Floor)(void);
void (*Spiny_State_Wall)(void);
void (*Spiny_State_Shoot_Wall)(void);

void Spiny_EnemyInfoHook(void) {
	Mod.Super(Spiny->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Spiny->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Spiny_State_Floor;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Spiny->hitboxSpiny;
	EnemyDefs[EnemyInfoSlot].states[1].func = Spiny_State_Shoot_Floor;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Spiny->hitboxSpiny;
	EnemyDefs[EnemyInfoSlot].states[2].func = Spiny_State_Wall;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Spiny->hitboxSpiny;
	EnemyDefs[EnemyInfoSlot].states[3].func = Spiny_State_Shoot_Wall;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &Spiny->hitboxSpiny;
	++EnemyInfoSlot;
}
