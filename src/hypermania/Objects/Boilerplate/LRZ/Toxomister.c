#include "Toxomister.h"

ObjectToxomister *Toxomister;
void (*Toxomister_State_CreateClouds)(void);

void Toxomister_EnemyInfoHook(void) {
	Mod.Super(Toxomister->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Toxomister->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Toxomister_State_CreateClouds;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Toxomister->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].destroy_func = Toxomister_DestroyCloud;
	++EnemyInfoSlot;
}

void Toxomister_DestroyCloud(EntityPlayer* player, Entity* e) {
	EntityToxomister* self = (EntityToxomister*)e;
	if (self->parent) destroyEntity(self->parent);
	BreakBadnik(player, e);
}