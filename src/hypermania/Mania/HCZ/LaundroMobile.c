#include "LaundroMobile.h"

ObjectWhirlpool* Whirlpool;
ObjectLaundroMobile* LaundroMobile;
void (*LaundroMobile_StateBoss_AwaitPlayer_Phase1)();
void (*LaundroMobile_StateBoss_SetupArena_Phase1)();
void (*LaundroMobile_StateBoss_Destroyed_Phase1)();
void (*LaundroMobile_StateBoss_Destroyed_Phase2)();
void (*LaundroMobile_StateBoss_Explode_Phase2)();

bool32 LaundroMobile_CheckVulnerable(Entity* self) {
	if (LaundroMobile->invincibilityTimer || ((EntityLaundroMobile*)self)->type != LAUNDROMOBILE_BOSS) return false;
	return (
	    ((EntityLaundroMobile*)self)->state != LaundroMobile_StateBoss_AwaitPlayer_Phase1
	 && ((EntityLaundroMobile*)self)->state != LaundroMobile_StateBoss_SetupArena_Phase1
	 && ((EntityLaundroMobile*)self)->state != LaundroMobile_StateBoss_Destroyed_Phase2
	 && ((EntityLaundroMobile*)self)->state != LaundroMobile_StateBoss_Explode_Phase2);
}

Hitbox* LaundroMobile_GetHitbox(Entity* self) { return &(LaundroMobile->hitboxBoss); }

void LaundroMobile_OnHit(EntityPlayer* player, Entity* self) {
	if (--LaundroMobile->health) {
		if (LaundroMobile->health == 8) {
			RSDK.StopSfx(LaundroMobile->sfxFan);
			RSDK.SetSpriteAnimation(LaundroMobile->aniFrames, 4, &((EntityLaundroMobile*)self)->propellerAnimator, true, 0);
			((EntityLaundroMobile*)self)->timer = 60;
			((EntityLaundroMobile*)self)->state = LaundroMobile_StateBoss_Destroyed_Phase1;
			} else {
			if (LaundroMobile->health < 8) {
				RSDK.SetSpriteAnimation(LaundroMobile->eggmanFrames, 3, &((EntityLaundroMobile*)self)->eggmanAnimator, true, 0);
			}
			else {
				RSDK.SetSpriteAnimation(LaundroMobile->eggmanFrames, 2, &((EntityLaundroMobile*)self)->eggmanAnimator, true, 0);
			}
			RSDK.PlaySfx(LaundroMobile->sfxHit, false, 255);
			LaundroMobile->invincibilityTimer = 30;
		}
	} else {
		SceneInfo->timeEnabled = false;
		Player_GiveScore(RSDK_GET_ENTITY(SLOT_PLAYER1, Player), 1000);
		RSDK.PlaySfx(LaundroMobile->sfxExplosion, false, 255);
		LaundroMobile->invincibilityTimer = 60;

		EntityWhirlpool* whirlpool          = ((EntityLaundroMobile*)self)->whirlpool;
		((EntityLaundroMobile*)self)->state = LaundroMobile_StateBoss_Destroyed_Phase2;
		if (whirlpool) {
			if (whirlpool->classID == Whirlpool->classID) whirlpool->activePlayers = -3;
			((EntityLaundroMobile*)self)->whirlpool = NULL;
		}
	}
}

void LaundroMobile_EnemyInfoHook() {
	Mod.Super(LaundroMobile->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(LaundroMobile->classID, LaundroMobile_CheckVulnerable, LaundroMobile_GetHitbox, LaundroMobile_OnHit, NULL, ATKFLAG_ISBOSS);
}