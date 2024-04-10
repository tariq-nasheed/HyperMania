#include "TurboTurtle.h"

ObjectTurboTurtle* TurboTurtle;

Hitbox* TurboTurtle_GetHitbox(Entity* self) { return &(TurboTurtle->hitboxBadnik); }

void TurboTurtle_EnemyInfoHook() {
	Mod.Super(TurboTurtle->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(TurboTurtle->classID, Generic_CheckVulnerable, TurboTurtle_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}