#include "MegaChopper.h"

ObjectMegaChopper* MegaChopper;
void (*MegaChopper_State_InWater)();
void (*MegaChopper_State_OutOfWater)();

bool32 MegaChopper_CheckVulnerable(Entity* self) {
	return (
	    ((EntityMegaChopper*)self)->state == MegaChopper_State_InWater
	 || ((EntityMegaChopper*)self)->state == MegaChopper_State_OutOfWater
	);
}

Hitbox* MegaChopper_GetHitbox(Entity* self) { return &(MegaChopper->hitboxBadnik); }

void MegaChopper_EnemyInfoHook() {
	Mod.Super(MegaChopper->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(MegaChopper->classID, MegaChopper_CheckVulnerable, MegaChopper_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}
