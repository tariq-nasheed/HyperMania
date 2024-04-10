#include "Blastoid.h"

ObjectBlastoid* Blastoid;
void (*Blastoid_State_Projectile)();

bool32 Blastoid_CheckVulnerable(Entity* self) {
	return (((EntityBlastoid*)self)->state != Blastoid_State_Projectile);
}

Hitbox* Blastoid_GetHitbox(Entity* self) { return &(Blastoid->hitboxBody); }

void Blastoid_OnHit(EntityPlayer* player, Entity* self) {
	EntityCollapsingPlatform *platform = RSDK_GET_ENTITY(RSDK.GetEntitySlot(self) - 1, CollapsingPlatform);
	if (platform->classID == CollapsingPlatform->classID) {
		platform->active        = ACTIVE_NORMAL;
		platform->collapseDelay = 30;
		platform->stoodPos.x    = self->position.x;
	}
	Generic_BadnikBreak(player, self, true);
}

void Blastoid_EnemyInfoHook() {
	Mod.Super(Blastoid->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Blastoid->classID, Blastoid_CheckVulnerable, Blastoid_GetHitbox, Blastoid_OnHit, NULL, ATKFLAG_NONE);
}