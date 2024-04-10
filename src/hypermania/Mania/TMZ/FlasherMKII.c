#include "FlasherMKII.h"

ObjectFlasherMKII* FlasherMKII;

Hitbox* FlasherMKII_GetHitbox(Entity* self) {
	return RSDK.GetHitbox(&((EntityFlasherMKII*)self)->animator, 0);
}

void FlasherMKII_OnHit(EntityPlayer* player, Entity* self) {
	RSDK.StopSfx(FlasherMKII->sfxZap);
	Generic_BadnikBreak(player, self, true);
}

void FlasherMKII_EnemyInfoHook() {
	Mod.Super(FlasherMKII->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(FlasherMKII->classID, Generic_CheckVulnerable, FlasherMKII_GetHitbox, FlasherMKII_OnHit, NULL, ATKFLAG_NONE);
}