#include "HeavyKing.h"

ObjectHeavyKing* HeavyKing;
void (*HeavyKing_State_JumpToTargetEmerald)();
void (*HeavyKing_State_Leaping)();
void (*HeavyKing_State_LeapToMasterEmerald)();
void (*HeavyKing_State_LandedOnMasterEmerald)();
void (*HeavyKing_State_ChargeStart)();
void (*HeavyKing_State_ChargeStop)();
void (*HeavyKing_State_PrepareHover)();
void (*HeavyKing_State_StartHovering)();
void (*HeavyKing_State_Hovering)();
void (*HeavyKing_State_LaserAttack)();
void (*HeavyKing_State_ExpandRingAttack)();
void (*HeavyKing_State_TwinChargeAttack)();
void (*HeavyKing_Hit)();

bool32 HeavyKing_CheckVulnerable(Entity* self) {
	if (((EntityHeavyKing*)self)->invincibilityTimer) return false;
	return (
	    ((EntityHeavyKing*)self)->state == HeavyKing_State_JumpToTargetEmerald
	 || ((EntityHeavyKing*)self)->state == HeavyKing_State_Leaping
	 || ((EntityHeavyKing*)self)->state == HeavyKing_State_LeapToMasterEmerald
	 || ((EntityHeavyKing*)self)->state == HeavyKing_State_LandedOnMasterEmerald
	 || ((EntityHeavyKing*)self)->state == HeavyKing_State_ChargeStart
	 || ((EntityHeavyKing*)self)->state == HeavyKing_State_ChargeStop
	 || ((EntityHeavyKing*)self)->state == HeavyKing_State_PrepareHover
	 || ((EntityHeavyKing*)self)->state == HeavyKing_State_StartHovering
	 || ((EntityHeavyKing*)self)->state == HeavyKing_State_Hovering
	 || ((EntityHeavyKing*)self)->state == HeavyKing_State_LaserAttack
	 || ((EntityHeavyKing*)self)->state == HeavyKing_State_ExpandRingAttack
	 || ((EntityHeavyKing*)self)->state == HeavyKing_State_TwinChargeAttack
	);
}

Hitbox* HeavyKing_GetHitbox(Entity* self) { return &(HeavyKing->hitboxBoss); }

void HeavyKing_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	HeavyKing_Hit();
	SceneInfo->entity = old_entity;
}

void HeavyKing_EnemyInfoHook() {
	Mod.Super(HeavyKing->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(HeavyKing->classID, HeavyKing_CheckVulnerable, HeavyKing_GetHitbox, HeavyKing_OnHit, NULL, ATKFLAG_ISBOSS);
}