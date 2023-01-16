#include "Newtron.h"

ObjectNewtron *Newtron;
void (*Newtron_State_StartFly)(void);
void (*Newtron_State_Fly)(void);
void (*Newtron_State_Shoot)(void);

void Newtron_EnemyInfoHook(void) {
	Mod.Super(Newtron->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Newtron->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Newtron_State_StartFly;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Newtron->hitboxShoot;
	EnemyDefs[EnemyInfoSlot].states[1].func = Newtron_State_Fly;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Newtron->hitboxShoot;
	EnemyDefs[EnemyInfoSlot].states[2].func = Newtron_State_Shoot;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Newtron->hitboxShoot;
	++EnemyInfoSlot;
}