#include "Buggernaut.h"

ObjectBuggernaut* Buggernaut;

Hitbox* Buggernaut_GetHitbox(Entity* self) { return &(Buggernaut->hitboxBadnik); }

void Buggernaut_EnemyInfoHook() {
	Mod.Super(Buggernaut->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Buggernaut->classID, Generic_CheckVulnerable, Buggernaut_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}