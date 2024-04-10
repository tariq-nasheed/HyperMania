#include "Toxomister.h"

ObjectToxomister* Toxomister;
void (*Toxomister_State_CreateClouds)();

bool32 Toxomister_CheckVulnerable(Entity* self) {
	return (((EntityToxomister*)self)->state == Toxomister_State_CreateClouds);
}

Hitbox* Toxomister_GetHitbox(Entity* self) { return &(Toxomister->hitboxBadnik); }

void Toxomister_OnHit(EntityPlayer* player, Entity* self) {
	if (((EntityToxomister*)self)->parent) destroyEntity(((EntityToxomister*)self)->parent);
	Generic_BadnikBreak(player, self, true);
}

void Toxomister_EnemyInfoHook() {
	Mod.Super(Toxomister->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Toxomister->classID, Toxomister_CheckVulnerable, Toxomister_GetHitbox, Toxomister_OnHit, NULL, ATKFLAG_NONE);
}