#include "HeavyMystic.h"

ObjectHeavyMystic* HeavyMystic;
void (*HeavyMystic_StateBoss_RougeHit)();
void (*HeavyMystic_StateBoss_MysticReveal)();
void (*HeavyMystic_StateBoss_FangIdle)();
void (*HeavyMystic_StateBoss_FangTell)();
void (*HeavyMystic_StateBoss_FangHop)();
void (*HeavyMystic_StateBoss_BarkIdle)();
void (*HeavyMystic_StateBoss_BarkPounding)();
void (*HeavyMystic_StateBoss_BarkJump)();
void (*HeavyMystic_StateBoss_BeanIdle)();
void (*HeavyMystic_StateBoss_BeanBomb1Throw)();
void (*HeavyMystic_StateBoss_BeanBomb2Throw)();
void (*HeavyMystic_StateBoss_BeanJump)();
void (*HeavyMystic_Hit)();

bool32 HeavyMystic_CheckVulnerable(Entity* self) {
	if (((EntityHeavyMystic*)self)->invincibilityTimer) return false;
	return (
	    ((EntityHeavyMystic*)self)->state == HeavyMystic_StateBoss_MysticReveal
	 || ((EntityHeavyMystic*)self)->state == HeavyMystic_StateBoss_FangIdle
	 || ((EntityHeavyMystic*)self)->state == HeavyMystic_StateBoss_FangTell
	 || ((EntityHeavyMystic*)self)->state == HeavyMystic_StateBoss_FangHop
	 || ((EntityHeavyMystic*)self)->state == HeavyMystic_StateBoss_BarkIdle
	 || ((EntityHeavyMystic*)self)->state == HeavyMystic_StateBoss_BarkPounding
	 || ((EntityHeavyMystic*)self)->state == HeavyMystic_StateBoss_BarkJump
	 || ((EntityHeavyMystic*)self)->state == HeavyMystic_StateBoss_BeanIdle
	 || ((EntityHeavyMystic*)self)->state == HeavyMystic_StateBoss_BeanBomb1Throw
	 || ((EntityHeavyMystic*)self)->state == HeavyMystic_StateBoss_BeanBomb2Throw
	 || ((EntityHeavyMystic*)self)->state == HeavyMystic_StateBoss_BeanJump
	);
}

Hitbox* HeavyMystic_GetHitbox(Entity* self) { return &(((EntityHeavyMystic*)self)->hitbox); }

void HeavyMystic_OnHit(EntityPlayer* player, Entity* self) {
	if (((EntityHeavyMystic*)self)->state != HeavyMystic_StateBoss_MysticReveal) {
		RSDK.PlaySfx(HeavyMystic->sfxImpact, false, 255);
		self->velocity.x = player->position.x < self->position.x ? 0x20000 : -0x20000;
		self->velocity.y = -0x40000;
		int32 frame = 3;
		switch (((EntityHeavyMystic*)self)->rougeID) {
			case 1: frame = 9;  break;
			case 2: frame = 15; break;
			default: break;
		}
		RSDK.SetSpriteAnimation(HeavyMystic->rouguesFrames, frame, &((EntityHeavyMystic*)self)->animator, true, 0);
		((EntityHeavyMystic*)self)->state = HeavyMystic_StateBoss_RougeHit;
	}
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	HeavyMystic_Hit();
	SceneInfo->entity = old_entity;
}

void HeavyMystic_EnemyInfoHook() {
	Mod.Super(HeavyMystic->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(HeavyMystic->classID, HeavyMystic_CheckVulnerable, HeavyMystic_GetHitbox, HeavyMystic_OnHit, NULL, ATKFLAG_ISBOSS);
}