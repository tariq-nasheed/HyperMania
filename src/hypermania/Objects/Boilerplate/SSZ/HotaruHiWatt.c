#include "HotaruHiWatt.h"

ObjectHotaruHiWatt* HotaruHiWatt;

void (*HotaruHiWatt_StateBoss_Appear)();
void (*HotaruHiWatt_StateBoss_FlyUp)();
void (*HotaruHiWatt_StateBoss_LaserAttackDelay)();
void (*HotaruHiWatt_StateBoss_ChargingLaser)();
void (*HotaruHiWatt_StateBoss_FinishedLaserAttack)();
void (*HotaruHiWatt_StateBoss_LaserAttack_Left)();
void (*HotaruHiWatt_StateBoss_LaserAttack_Right)();
void (*HotaruHiWatt_StateHotaru_Charging)();
void (*HotaruHiWatt_StateHotaru_Attacking)();
void (*HotaruHiWatt_StateHotaru_FinishedAttack)();
void (*HotaruHiWatt_StateHotaru_EndAttackSequence)();
void (*HotaruHiWatt_StateHotaruPair_AttackMovingDown)();
void (*HotaruHiWatt_StateHotaruPair_AttackMovingUp)();
void (*HotaruHiWatt_SetupHHWReappear)();
void (*HotaruHiWatt_SpawnPairHotarus)();
void (*HotaruHiWatt_Hit)();

bool32 HotaruHiWatt_CheckVulnerable(Entity* self) {
	const uint32 index = self->classID - AttackableClasses_startidx;
	AttackableClasses[index].flags &= ~ATKFLAG_ISBOSS;
	if (((EntityHotaruHiWatt*)self)->type == HHW_BOSS) {
		AttackableClasses[index].flags |= ATKFLAG_ISBOSS;
	}

	if (((EntityHotaruHiWatt*)self)->invincibilityTimer) return false;
	return (
	    ((EntityHotaruHiWatt*)self)->state == HotaruHiWatt_StateBoss_Appear
	 || ((EntityHotaruHiWatt*)self)->state == HotaruHiWatt_StateBoss_FlyUp
	 || ((EntityHotaruHiWatt*)self)->state == HotaruHiWatt_StateBoss_LaserAttackDelay
	 || ((EntityHotaruHiWatt*)self)->state == HotaruHiWatt_StateBoss_LaserAttack_Left
	 || ((EntityHotaruHiWatt*)self)->state == HotaruHiWatt_StateBoss_LaserAttack_Right
	 || ((EntityHotaruHiWatt*)self)->state == HotaruHiWatt_StateBoss_ChargingLaser
	 || ((EntityHotaruHiWatt*)self)->state == HotaruHiWatt_StateBoss_FinishedLaserAttack
	 || ((EntityHotaruHiWatt*)self)->state == HotaruHiWatt_StateHotaru_Charging
	 || ((EntityHotaruHiWatt*)self)->state == HotaruHiWatt_StateHotaru_Attacking
	 || ((EntityHotaruHiWatt*)self)->state == HotaruHiWatt_StateHotaru_FinishedAttack
	 || ((EntityHotaruHiWatt*)self)->state == HotaruHiWatt_StateHotaru_EndAttackSequence
	 || ((EntityHotaruHiWatt*)self)->state == HotaruHiWatt_StateHotaruPair_AttackMovingDown
	 || ((EntityHotaruHiWatt*)self)->state == HotaruHiWatt_StateHotaruPair_AttackMovingUp
	);
}

Hitbox* HotaruHiWatt_GetHitbox(Entity* self) { return &(((EntityHotaruHiWatt*)self)->hitbox); }

void HotaruHiWatt_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	if (((EntityHotaruHiWatt*)self)->type == HHW_BOSS) {
		HotaruHiWatt_Hit();
	} else {
		if (((EntityHotaruHiWatt*)self)->type == HHW_SINGLE_HOTARU) {
			HotaruHiWatt_SpawnPairHotarus();
		} else {
			int32 hotaruPairCount = 0;
			foreach_active(HotaruHiWatt, boss) {
				if (boss->type == HHW_PAIR_HOTARU)
				hotaruPairCount++;
			}

			if (hotaruPairCount == 1) HotaruHiWatt_SetupHHWReappear();
		}
		Generic_BadnikBreak(player, self, true);
	}
	SceneInfo->entity = old_entity;
}

void HotaruHiWatt_EnemyInfoHook() {
	Mod.Super(HotaruHiWatt->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(HotaruHiWatt->classID, HotaruHiWatt_CheckVulnerable, HotaruHiWatt_GetHitbox, HotaruHiWatt_OnHit, NULL, 0);
}