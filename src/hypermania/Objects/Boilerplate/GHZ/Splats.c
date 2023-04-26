#include "Splats.h"

ObjectSplats *Splats;
void (*Splats_State_BounceAround)(void);
void (*Splats_State_JumpOutOfJar)(void);
void (*Splats_State_HandleBouncing)(void);
void (*Splats_State_HandleLanding)(void);
void (*Splats_State_NoMoreJumps)(void);

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
		if (parent) {
			if (parent->classID == Splats->classID) --parent->activeCount;
		}
	}
	Generic_BadnikBreak(player, self, true);
}

void Splats_EnemyInfoHook(void) {
	Mod.Super(Splats->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Splats->classID, Splats_CheckVulnerable, Splats_GetHitbox, Splats_OnHit, NULL, ATKFLAG_NONE);
}