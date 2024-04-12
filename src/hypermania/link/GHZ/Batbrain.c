#include "Batbrain.h"

ObjectBatbrain* Batbrain;

Hitbox* Batbrain_GetHitbox(Entity* self) { return &(Batbrain->hitboxBadnik); }

void Batbrain_EnemyInfoHook() {
	Mod.Super(Batbrain->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Batbrain->classID, Generic_CheckVulnerable, Batbrain_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}