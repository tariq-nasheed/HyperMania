#include "MicDrop.h"

ObjectMicDrop* MicDrop;

Hitbox* MicDrop_GetHitbox(Entity* self) { return &(MicDrop->hitboxBadnik); }

void MicDrop_AdjustPos(Entity* self) {
	self->position.x = (((((EntityMicDrop*)self)->radius + 25) * RSDK.Cos512(self->angle + 128)) << 7) + ((EntityMicDrop*)self)->startPos.x;
	self->position.y = (((((EntityMicDrop*)self)->radius + 25) * RSDK.Sin512(self->angle + 128)) << 7) + ((EntityMicDrop*)self)->startPos.y;
}

void MicDrop_EnemyInfoHook() {
	Mod.Super(MicDrop->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(MicDrop->classID, Generic_CheckVulnerable, MicDrop_GetHitbox, Generic_OnHit,MicDrop_AdjustPos, ATKFLAG_NONE);
}