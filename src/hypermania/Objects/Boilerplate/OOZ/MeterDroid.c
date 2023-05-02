#include "MeterDroid.h"

ObjectMeterDroid* MeterDroid;
void (*MeterDroid_State_TurningValve)();
void (*MeterDroid_State_StopTurningValve)();
void (*MeterDroid_State_WatchPlatformsPopUp)();
void (*MeterDroid_State_Destroyed)();
void (*MeterDroid_State_FinishAct)();
void (*MeterDroid_Hit)();

bool32 MeterDroid_CheckVulnerable(Entity* self) {
	if (((EntityMeterDroid*)self)->invincibilityTimer) return false;
	return (
	    ((EntityMeterDroid*)self)->state != MeterDroid_State_TurningValve
	 && ((EntityMeterDroid*)self)->state != MeterDroid_State_StopTurningValve
	 && ((EntityMeterDroid*)self)->state != MeterDroid_State_WatchPlatformsPopUp
	 && ((EntityMeterDroid*)self)->state != MeterDroid_State_Destroyed
	 && ((EntityMeterDroid*)self)->state != MeterDroid_Hit
	);
}

Hitbox* MeterDroid_GetHitbox(Entity* self) { return &(MeterDroid->hitboxBoss); }

void MeterDroid_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	MeterDroid_Hit();
	SceneInfo->entity = old_entity;
}

void MeterDroid_EnemyInfoHook() {
	Mod.Super(MeterDroid->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(MeterDroid->classID, MeterDroid_CheckVulnerable, MeterDroid_GetHitbox, MeterDroid_OnHit, NULL, ATKFLAG_ISBOSS);
}