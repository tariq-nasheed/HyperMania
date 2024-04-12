#include "Shiversaw.h"

ObjectShiversaw* Shiversaw;
void (*Shiversaw_State_Idle)();
void (*Shiversaw_State_MoveToPlayer)();
void (*Shiversaw_State_HitRecoil)();
void (*Shiversaw_Hit)();

bool32 Shiversaw_CheckVulnerable(Entity* self) {
	if (Shiversaw->invincibilityTimer) return false;
	return (
	    ((EntityShiversaw*)self)->state == Shiversaw_State_Idle
	 || ((EntityShiversaw*)self)->state == Shiversaw_State_MoveToPlayer
	 || ((EntityShiversaw*)self)->state == Shiversaw_State_HitRecoil
	);
}

Hitbox* Shiversaw_GetHitbox(Entity* self) { return &(Shiversaw->hitboxBoss); }

void Shiversaw_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	Shiversaw_Hit();
	SceneInfo->entity = old_entity;
}

void Shiversaw_EnemyInfoHook(void) {
	Mod.Super(Shiversaw->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Shiversaw->classID, Shiversaw_CheckVulnerable, Shiversaw_GetHitbox, Shiversaw_OnHit, NULL, ATKFLAG_ISBOSS);
}