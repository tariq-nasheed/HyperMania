#include "Clucker.h"

ObjectClucker* Clucker;
void (*Clucker_State_Destroyed)();
void (*Clucker_State_Egg)();

bool32 Clucker_CheckVulnerable(Entity* self) {
	return (
	    ((EntityClucker*)self)->state != Clucker_State_Destroyed
	 && ((EntityClucker*)self)->state != Clucker_State_Egg
	);
}

Hitbox* Clucker_GetHitbox(Entity* self) { return &(Clucker->hitboxBadnik); }

void Clucker_OnHit(EntityPlayer* player, Entity* self) {
	if (((EntityClucker*)self)->hasParent) {
		Generic_BadnikBreak(player, self, true);
	} else {
		((EntityClucker*)self)->yOffset = -0x7FFFFFFF;
		((EntityClucker*)self)->state = Clucker_State_Destroyed;
		Generic_BadnikBreak(player, self, false);
	}
}

void Clucker_AdjustPos(Entity* self) {
	if ((self->direction & FLIP_Y)) {
		self->position.y -= ((EntityClucker*)self)->yOffset;
	} else {
		self->position.y += ((EntityClucker*)self)->yOffset;
	}
}

void Clucker_EnemyInfoHook() {
	Mod.Super(Clucker->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Clucker->classID, Clucker_CheckVulnerable, Clucker_GetHitbox, Clucker_OnHit, Clucker_AdjustPos, ATKFLAG_NONE);
}