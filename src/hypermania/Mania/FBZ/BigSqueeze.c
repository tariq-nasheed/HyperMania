#include "BigSqueeze.h"

ObjectBigSqueeze *BigSqueeze;
void (*BigSqueeze_StateBoss_Idle)();
void (*BigSqueeze_StateBoss_Electrified)();
void (*BigSqueeze_Hit)();

bool32 BigSqueeze_CheckVulnerable(Entity* self) {
	if (((EntityBigSqueeze*)self)->invincibilityTimer) return false;
	return (
	    ((EntityBigSqueeze*)self)->state == BigSqueeze_StateBoss_Idle
	 || ((EntityBigSqueeze*)self)->state == BigSqueeze_StateBoss_Electrified
	);
}

Hitbox* BigSqueeze_GetHitbox(Entity* self) { return &(((EntityBigSqueeze*)self)->hitbox); }

void BigSqueeze_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	BigSqueeze_Hit();
	SceneInfo->entity = old_entity;
}

void BigSqueeze_EnemyInfoHook() {
	Mod.Super(BigSqueeze->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(BigSqueeze->classID, BigSqueeze_CheckVulnerable, BigSqueeze_GetHitbox, BigSqueeze_OnHit, NULL, ATKFLAG_ISBOSS);
}