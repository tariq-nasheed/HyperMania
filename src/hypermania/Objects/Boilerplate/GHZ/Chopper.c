#include "Chopper.h"

ObjectChopper* Chopper;
void (*Chopper_State_Jump)();

Hitbox* Chopper_GetHitbox(Entity* self) {
	if (((EntityChopper*)self)->state == Chopper_State_Jump) return &(Chopper->hitboxJump);
	return &(Chopper->hitboxSwim);
}

void Chopper_EnemyInfoHook() {
	Mod.Super(Chopper->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Chopper->classID, Generic_CheckVulnerable, Chopper_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}