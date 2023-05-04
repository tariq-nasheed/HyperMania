#include "Drillerdroid.h"

ObjectDrillerdroid* Drillerdroid;
void (*Drillerdroid_State_SetupArena)();
void (*Drillerdroid_State_AwaitPlayer)();
void (*Drillerdroid_State_FinishDrilling)();
void (*Drillerdroid_State_JumpTargeting)();
void (*Drillerdroid_State_DecidingDropPos)();
void (*Drillerdroid_State_DropFailReset)();
void (*Drillerdroid_State_Destroyed)();
void (*Drillerdroid_State_Finish)();
void (*Drillerdroid_State_DropSignPost)();
void (*Drillerdroid_State_Target)();
void (*Drillerdroid_Hit)();

bool32 Drillerdroid_CheckVulnerable(Entity* self) {
	if (((EntityDrillerdroid*)self)->invincibilityTimer || Drillerdroid->armorHealth > 1) return false;
	return (
	    ((EntityDrillerdroid*)self)->state != Drillerdroid_State_SetupArena
	 && ((EntityDrillerdroid*)self)->state != Drillerdroid_State_AwaitPlayer
	 && ((EntityDrillerdroid*)self)->state != Drillerdroid_State_FinishDrilling
	 && ((EntityDrillerdroid*)self)->state != Drillerdroid_State_JumpTargeting
	 && ((EntityDrillerdroid*)self)->state != Drillerdroid_State_DecidingDropPos
	 && ((EntityDrillerdroid*)self)->state != Drillerdroid_State_DropFailReset
	 && ((EntityDrillerdroid*)self)->state != Drillerdroid_State_Destroyed
	 && ((EntityDrillerdroid*)self)->state != Drillerdroid_State_Finish
	 && ((EntityDrillerdroid*)self)->state != Drillerdroid_State_DropSignPost
	 && ((EntityDrillerdroid*)self)->state != Drillerdroid_State_Target
	);
}

Hitbox* Drillerdroid_GetHitbox(Entity* self) { return &(Drillerdroid->hitboxCore); }

void Drillerdroid_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	Drillerdroid_Hit();
	SceneInfo->entity = old_entity;
}

void Drillerdroid_EnemyInfoHook() {
	Mod.Super(Drillerdroid->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Drillerdroid->classID, Drillerdroid_CheckVulnerable, Drillerdroid_GetHitbox, Drillerdroid_OnHit, NULL, ATKFLAG_ISBOSS);
}