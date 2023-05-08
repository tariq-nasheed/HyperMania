#include "PhantomEgg.h"

ObjectPhantomShield* PhantomShield;
ObjectPhantomEgg* PhantomEgg;
void (*PhantomEgg_State_MoveAround)();
void (*PhantomEgg_State_Attack_Jumped)();
void (*PhantomEgg_State_Attack_JumpLand)();
void (*PhantomEgg_State_Attack_JumpAttack)();
void (*PhantomEgg_State_Attack_CableShock)();
void (*PhantomEgg_Hit)();

bool32 PhantomEgg_CheckVulnerable(Entity* self) {
	if (((EntityPhantomEgg*)self)->invincibilityTimer || RSDK.GetEntityCount(PhantomShield->classID, true) > 0) return false;
	return (
	    ((EntityPhantomEgg*)self)->state == PhantomEgg_State_MoveAround
	 || ((EntityPhantomEgg*)self)->state == PhantomEgg_State_Attack_Jumped
	 || ((EntityPhantomEgg*)self)->state == PhantomEgg_State_Attack_JumpLand
	 || ((EntityPhantomEgg*)self)->state == PhantomEgg_State_Attack_JumpAttack
	 || ((EntityPhantomEgg*)self)->state == PhantomEgg_State_Attack_CableShock
	);
}

Hitbox* PhantomEgg_GetHitbox(Entity* self) { return &(((EntityPhantomEgg*)self)->hitbox); }

void PhantomEgg_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	SceneInfo->entitySlot = RSDK.GetEntitySlot(self);
	PhantomEgg_Hit();
	SceneInfo->entity = old_entity;
	SceneInfo->entitySlot = RSDK.GetEntitySlot(old_entity);
}

void PhantomEgg_EnemyInfoHook() {
	Mod.Super(PhantomEgg->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(PhantomEgg->classID, PhantomEgg_CheckVulnerable, PhantomEgg_GetHitbox, PhantomEgg_OnHit, NULL, ATKFLAG_ISBOSS);
}