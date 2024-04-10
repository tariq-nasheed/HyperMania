#include "DrillerdroidO.h"

ObjectDrillerdroidO* DrillerdroidO;
void (*DrillerdroidO_State_Dropping)();
void (*DrillerdroidO_State_Landed)();
void (*DrillerdroidO_State_LandRecoil)();
void (*DrillerdroidO_State_BeginDrilling)();
void (*DrillerdroidO_State_Drilling)();
void (*DrillerdroidO_State_FinishDrilling)();
void (*DrillerdroidO_State_Overheat)();
void (*DrillerdroidO_State_OverheatRecoil)();
void (*DrillerdroidO_State_JumpTargetDelay)();
void (*DrillerdroidO_State_OverheatRecoil_DestroyedSegment)();
void (*DrillerdroidO_State_Cooldown)();
void (*DrillerdroidO_State_ResetFromCooldown)();
void (*DrillerdroidO_State_Destroyed)();

bool32 DrillerdroidO_CheckVulnerable(Entity* self) {
	if (((EntityDrillerdroidO*)self)->invincibilityTimer) return false;
	return (
	    ((EntityDrillerdroidO*)self)->state == DrillerdroidO_State_Dropping
	 || ((EntityDrillerdroidO*)self)->state == DrillerdroidO_State_Landed
	 || ((EntityDrillerdroidO*)self)->state == DrillerdroidO_State_LandRecoil
	 || ((EntityDrillerdroidO*)self)->state == DrillerdroidO_State_BeginDrilling
	 || ((EntityDrillerdroidO*)self)->state == DrillerdroidO_State_Drilling
	 || ((EntityDrillerdroidO*)self)->state == DrillerdroidO_State_FinishDrilling
	 || ((EntityDrillerdroidO*)self)->state == DrillerdroidO_State_Overheat
	 || ((EntityDrillerdroidO*)self)->state == DrillerdroidO_State_OverheatRecoil
	 || ((EntityDrillerdroidO*)self)->state == DrillerdroidO_State_JumpTargetDelay
	 || ((EntityDrillerdroidO*)self)->state == DrillerdroidO_State_OverheatRecoil_DestroyedSegment
	 || ((EntityDrillerdroidO*)self)->state == DrillerdroidO_State_Cooldown
	 || ((EntityDrillerdroidO*)self)->state == DrillerdroidO_State_ResetFromCooldown
	);
}

Hitbox* DrillerdroidO_GetHitbox(Entity* self) { return &(DrillerdroidO->hitboxCore); }

void DrillerdroidO_OnHit(EntityPlayer* player, Entity* self) {
	if (!--((EntityDrillerdroidO*)self)->health) {
		SceneInfo->timeEnabled = false;
		Player_GiveScore(RSDK_GET_ENTITY(SLOT_PLAYER1, Player), 1000);
		((EntityDrillerdroidO*)self)->invincibilityTimer = 60;
		DrillerdroidO->emitFireballs                     = false;
		((EntityDrillerdroidO*)self)->state              = DrillerdroidO_State_Destroyed;
	} else {
		RSDK.PlaySfx(DrillerdroidO->sfxHit, false, 255);
		((EntityDrillerdroidO*)self)->invincibilityTimer = 30;
	}
}

void DrillerdroidO_EnemyInfoHook() {
	Mod.Super(DrillerdroidO->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(DrillerdroidO->classID, DrillerdroidO_CheckVulnerable, DrillerdroidO_GetHitbox, DrillerdroidO_OnHit, NULL, ATKFLAG_ISBOSS);
}