#include "Kanabun.h"

ObjectKanabun* Kanabun;

Hitbox* Kanabun_GetHitbox(Entity* self) { return &(Kanabun->hitboxBadnik); }

void Kanabun_EnemyInfoHook() {
	Mod.Super(Kanabun->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Kanabun->classID, Generic_CheckVulnerable, Kanabun_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}