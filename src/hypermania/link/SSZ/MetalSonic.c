#include "MetalSonic.h"

ObjectMetalSonic* MetalSonic;

#if !MANIA_USE_PLUS

void (*MetalSonic_State_Hover_Phase2)();
void (*MetalSonic_State_FinishAttack_Phase2)();
void (*MetalSonic_Hit)();

bool32 MetalSonic_CheckVulnerable(Entity* self) {
	if (((EntityMetalSonic*)self)->invincibilityTimer) return false;
	return (
	    ((EntityMetalSonic*)self)->state == MetalSonic_State_Hover_Phase2
	 || ((EntityMetalSonic*)self)->state == MetalSonic_State_FinishAttack_Phase2
	);
}

Hitbox* MetalSonic_GetHitbox(Entity* self) { return ((EntityMetalSonic*)self)->metalSonicAnimator.animationID == MS_ANI_FLY ? &MetalSonic->hitboxDash : &MetalSonic->hitboxHover; }

void MetalSonic_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	MetalSonic_Hit();
	SceneInfo->entity = old_entity;
}

void MetalSonic_EnemyInfoHook() {
	Mod.Super(MetalSonic->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(MetalSonic->classID, MetalSonic_CheckVulnerable, MetalSonic_GetHitbox, MetalSonic_OnHit, NULL, ATKFLAG_ISBOSS);
}

#endif