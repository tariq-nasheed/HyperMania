#include "Cactula.h"

ObjectCactula* Cactula;

Hitbox* Cactula_GetHitbox(Entity* self) { return &(Cactula->hitboxBadnik); }

void Cactula_EnemyInfoHook() {
	Mod.Super(Cactula->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Cactula->classID, Generic_CheckVulnerable, Cactula_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}