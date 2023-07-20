#include "TurboSpiker.h"

ObjectTurboSpiker* TurboSpiker;

Hitbox* TurboSpiker_GetHitbox(Entity* self) { return &(TurboSpiker->hitboxBadnik); }

void TurboSpiker_OnHit(EntityPlayer* player, Entity* self) {
	if (((EntityTurboSpiker*)self)->spike) destroyEntity(((EntityTurboSpiker*)self)->spike);
	Generic_BadnikBreak(player, self, true);
}

void TurboSpiker_EnemyInfoHook() {
	Mod.Super(TurboSpiker->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(TurboSpiker->classID, Generic_CheckVulnerable, TurboSpiker_GetHitbox, TurboSpiker_OnHit, NULL, ATKFLAG_NONE);
}
