#include "Pointdexter.h"

ObjectPointdexter* Pointdexter;

Hitbox* Pointdexter_GetHitbox(Entity* self) { return &(Pointdexter->hitbox); }

void Pointdexter_EnemyInfoHook() {
	Mod.Super(Pointdexter->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Pointdexter->classID, Generic_CheckVulnerable, Pointdexter_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}
