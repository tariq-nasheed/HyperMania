#include "AmoebaDroid.h"

ObjectAmoebaDroid *AmoebaDroid;
void (*AmoebaDroid_State_DropIn)();
void (*AmoebaDroid_State_DropIntoPool)();
void (*AmoebaDroid_State_SurfaceFromPool)();
void (*AmoebaDroid_State_ChooseAttack)();
void (*AmoebaDroid_State_ExitPool)();
void (*AmoebaDroid_State_BounceAttack)();
void (*AmoebaDroid_State_GatherBlobs)();
void (*AmoebaDroid_State_SpinBlobs)();
void (*AmoebaDroid_Hit)();

bool32 AmoebaDroid_CheckVulnerable(Entity* self) {
	if (((EntityAmoebaDroid*)self)->invincibleTimer) return false;
	return (
	    ((EntityAmoebaDroid*)self)->state == AmoebaDroid_State_DropIn
	 || ((EntityAmoebaDroid*)self)->state == AmoebaDroid_State_DropIntoPool
	 || ((EntityAmoebaDroid*)self)->state == AmoebaDroid_State_SurfaceFromPool
	 || ((EntityAmoebaDroid*)self)->state == AmoebaDroid_State_ChooseAttack
	 || ((EntityAmoebaDroid*)self)->state == AmoebaDroid_State_ExitPool
	 || ((EntityAmoebaDroid*)self)->state == AmoebaDroid_State_BounceAttack
	 || ((EntityAmoebaDroid*)self)->state == AmoebaDroid_State_GatherBlobs
	 || ((EntityAmoebaDroid*)self)->state == AmoebaDroid_State_SpinBlobs
	);
}

Hitbox* AmoebaDroid_GetHitbox(Entity* self) { return &(((EntityAmoebaDroid*)self)->hitbox); }

void AmoebaDroid_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	AmoebaDroid_Hit();
	SceneInfo->entity = old_entity;
}

void AmoebaDroid_EnemyInfoHook() {
	Mod.Super(AmoebaDroid->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(AmoebaDroid->classID, AmoebaDroid_CheckVulnerable, AmoebaDroid_GetHitbox, AmoebaDroid_OnHit, NULL, ATKFLAG_ISBOSS);
}