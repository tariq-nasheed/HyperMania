#include "Bumpalo.h"

ObjectBumpalo* Bumpalo;

Hitbox* Bumpalo_GetHitbox(Entity* self) { return &(Bumpalo->hitboxBadnik); }

void Bumpalo_EnemyInfoHook() {
	Mod.Super(Bumpalo->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Bumpalo->classID, Generic_CheckVulnerable, Bumpalo_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}