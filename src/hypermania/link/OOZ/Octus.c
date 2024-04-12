#include "Octus.h"

ObjectOctus* Octus;
void (*Octus_State_Shot)();

bool32 Octus_CheckVulnerable(Entity* self) {
	return (((EntityOctus*)self)->state != Octus_State_Shot);
}

Hitbox* Octus_GetHitbox(Entity* self) { return &(Octus->hitboxBadnik); }

void Octus_EnemyInfoHook() {
	Mod.Super(Octus->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Octus->classID, Octus_CheckVulnerable, Octus_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}