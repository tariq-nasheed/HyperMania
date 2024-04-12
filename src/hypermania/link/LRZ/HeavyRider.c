#include "HeavyRider.h"

ObjectHeavyRider* HeavyRider;

void (*HeavyRider_State_Moving)();
void (*HeavyRider_State_Turning)();
void (*HeavyRider_Hit)();

bool32 HeavyRider_CheckVulnerable(Entity* self) {
	if (HeavyRider->invincibilityTimer) return false;
	return (
	    ((EntityHeavyRider*)self)->state == HeavyRider_State_Moving
	 || ((EntityHeavyRider*)self)->state == HeavyRider_State_Turning
	);
}

Hitbox* HeavyRider_GetHitbox(Entity* self) { return &(HeavyRider->hitboxRider); }

void HeavyRider_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	HeavyRider_Hit();
	SceneInfo->entity = old_entity;
}

void HeavyRider_EnemyInfoHook() {
	Mod.Super(HeavyRider->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(HeavyRider->classID, HeavyRider_CheckVulnerable, HeavyRider_GetHitbox, HeavyRider_OnHit, NULL, ATKFLAG_ISBOSS);
}