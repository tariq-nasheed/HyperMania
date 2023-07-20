#include "Vultron.h"

ObjectVultron* Vultron;

Hitbox* Vultron_GetHitbox(Entity* self) {
	return RSDK.GetHitbox(&((EntityVultron*)self)->bodyAnimator, 0);
}

void Vultron_AdjustPos(Entity* self) {
	Hitbox* hb = RSDK.GetHitbox(&((EntityVultron*)self)->bodyAnimator, 0);
	int32 left = (hb->left << 16) + (((hb->right - hb->left) << 15) & 0xFFFF0000);
	int32 top  = (hb->top << 16) + (((hb->bottom - hb->top) << 15) & 0xFFFF0000);
	if (self->direction == FLIP_X) left = -left;

	self->position.x += left;
	self->position.y += top;
}

void Vultron_EnemyInfoHook(void) {
	Mod.Super(Vultron->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Vultron->classID, Generic_CheckVulnerable, Vultron_GetHitbox, Generic_OnHit, Vultron_AdjustPos, ATKFLAG_NONE);
}
