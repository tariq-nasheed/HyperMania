#include "BigSqueeze.h"

ObjectBigSqueeze *BigSqueeze;
void (*BigSqueeze_StateBoss_Idle)(void);
void (*BigSqueeze_StateBoss_Electrified)(void);
void (*BigSqueeze_HandleWallCollisions)(void);
void (*BigSqueeze_StateBoss_Destroyed)(void);
void BigSqueeze_EnemyInfoHook(void) {
	Mod.Super(BigSqueeze->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = BigSqueeze->classID;
	EnemyDefs[EnemyInfoSlot].animal = false;
	EnemyDefs[EnemyInfoSlot].boss = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = BigSqueeze_StateBoss_Idle;
	EnemyDefs[EnemyInfoSlot].states[1].func = BigSqueeze_StateBoss_Electrified;
	EnemyDefs[EnemyInfoSlot].hitbox_func = BigSqueeze_GetHitbox;
	EnemyDefs[EnemyInfoSlot].destroy_func = BigSqueeze_TakeHit;
	++EnemyInfoSlot;
}

Hitbox* BigSqueeze_GetHitbox(Entity* e) {
	EntityBigSqueeze* self = (EntityBigSqueeze*)e;
	return &self->hitbox;
}

void BigSqueeze_TakeHit(EntityPlayer* player, Entity* e) {
	EntityBigSqueeze* self = (EntityBigSqueeze*)e;
	if (!self->invincibilityTimer) {
		if (--self->timer <= 0) {
			foreach_active(BigSqueeze, boss) {
				if (boss->type == BIGSQUEEZE_CRUSHER_L || boss->type == BIGSQUEEZE_CRUSHER_R) {
					boss->state = BigSqueeze_HandleWallCollisions;
				}
			}

			RSDK.SetSpriteAnimation(-1, 0, &self->electricAnimator, true, 0);

			self->state            = BigSqueeze_StateBoss_Destroyed;
			self->setupTimer       = 0;
			SceneInfo->timeEnabled = false;
			EntityPlayer *player   = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
			Player_GiveScore(player, 1000);
		} else {
			self->invincibilityTimer = 48;
			RSDK.PlaySfx(BigSqueeze->sfxBossHit, false, 255);
		}
	}
}