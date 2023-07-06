#include "Shutterbug.h"

ObjectShutterbug* Shutterbug;

Hitbox* Shutterbug_GetHitbox(Entity* self) { return &(Shutterbug->hitboxBadnik); }

void Shutterbug_EnemyInfoHook() {
	Mod.Super(Shutterbug->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Shutterbug->classID, Generic_CheckVulnerable, Shutterbug_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}