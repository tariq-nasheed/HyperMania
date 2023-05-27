#include "Splats.h"

ObjectSplats* Splats;
void (*Splats_State_BounceAround)();
void (*Splats_State_JumpOutOfJar)();
void (*Splats_State_HandleBouncing)();
void (*Splats_State_HandleLanding)();
void (*Splats_State_NoMoreJumps)();

bool32 Splats_CheckVulnerable(Entity* self) {
	return (
	    ((EntitySplats*)self)->state == Splats_State_BounceAround
	 || ((EntitySplats*)self)->state == Splats_State_JumpOutOfJar
	 || ((EntitySplats*)self)->state == Splats_State_HandleBouncing
	 || ((EntitySplats*)self)->state == Splats_State_HandleLanding
	 || ((EntitySplats*)self)->state == Splats_State_NoMoreJumps
	);
}

Hitbox* Splats_GetHitbox(Entity* self) { return &(Splats->hitboxBadnikGHZ); }

void Splats_OnHit(EntityPlayer* player, Entity* self) {
	if (Splats->initialState != Splats_State_BounceAround) {
		EntitySplats* parent = (EntitySplats*)(((EntitySplats*)self)->parent);
		if (parent || parent->classID == Splats->classID) --parent->activeCount;
	}
	Generic_BadnikBreak(player, self, true);
}

void Splats_EnemyInfoHook() {
	Mod.Super(Splats->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Splats->classID, Splats_CheckVulnerable, Splats_GetHitbox, Splats_OnHit, NULL, ATKFLAG_NONE);
}