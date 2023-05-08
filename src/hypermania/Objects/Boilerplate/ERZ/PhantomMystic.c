#include "PhantomMystic.h"

ObjectPhantomMystic* PhantomMystic;
void (*PhantomMystic_State_CupBlast)();
void (*PhantomMystic_State_MoveCupsToMystic)();
void (*PhantomMystic_Hit)();

bool32 PhantomMystic_CheckVulnerable(Entity* self) {
	if (((EntityPhantomMystic*)self)->invincibilityTimer) return false;
	return (
	    ((EntityPhantomMystic*)self)->state == PhantomMystic_State_CupBlast
	 || ((EntityPhantomMystic*)self)->state == PhantomMystic_State_MoveCupsToMystic
	);
}

Hitbox* PhantomMystic_GetHitbox(Entity* self) { return &(((EntityPhantomMystic*)self)->hitbox); }

void PhantomMystic_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	SceneInfo->entitySlot = RSDK.GetEntitySlot(self);
	PhantomMystic_Hit();
	SceneInfo->entity = old_entity;
	SceneInfo->entitySlot = RSDK.GetEntitySlot(old_entity);
}

void PhantomMystic_AdjustPos(Entity* self) { self->position = ((EntityPhantomMystic*)self)->mysticPos; }

void PhantomMystic_EnemyInfoHook() {
	Mod.Super(PhantomMystic->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(PhantomMystic->classID, PhantomMystic_CheckVulnerable, PhantomMystic_GetHitbox, PhantomMystic_OnHit, PhantomMystic_AdjustPos, ATKFLAG_ISBOSS);
}