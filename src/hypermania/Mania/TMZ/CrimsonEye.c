#include "CrimsonEye.h"

ObjectCrimsonEye* CrimsonEye;
void (*CrimsonEye_StateCore_ContainerActive)();
void (*CrimsonEye_StateCore_Hovering)();
void (*CrimsonEye_StateCore_ImpactLift)();
void (*CrimsonEye_Hit)();

bool32 CrimsonEye_CheckVulnerable(Entity* self) {
	if (CrimsonEye->invincibilityTimer) return false;
	return (
	    ((EntityCrimsonEye*)self)->state == CrimsonEye_StateCore_ContainerActive
	 || ((EntityCrimsonEye*)self)->state == CrimsonEye_StateCore_Hovering
	 || ((EntityCrimsonEye*)self)->state == CrimsonEye_StateCore_ImpactLift
	);
}

Hitbox* CrimsonEye_GetHitbox(Entity* self) { return &(CrimsonEye->hitboxEye); }

void CrimsonEye_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	SceneInfo->entitySlot = RSDK.GetEntitySlot(self);
	CrimsonEye_Hit();
	SceneInfo->entity = old_entity;
	SceneInfo->entitySlot = RSDK.GetEntitySlot(old_entity);
}

void CrimsonEye_AdjustPos(Entity* self) { self->position = CrimsonEye->eyePositions[0]; }

void CrimsonEye_EnemyInfoHook() {
	Mod.Super(CrimsonEye->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(CrimsonEye->classID, CrimsonEye_CheckVulnerable, CrimsonEye_GetHitbox, CrimsonEye_OnHit, CrimsonEye_AdjustPos, ATKFLAG_ISBOSS);
}