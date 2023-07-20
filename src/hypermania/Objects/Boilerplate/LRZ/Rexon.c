#include "Rexon.h"

ObjectRexon *Rexon;
void (*Rexon_State_Hidden)();
void (*Rexon_State_Rising)();
void (*Rexon_State_Shooting)();
void (*Rexon_State_Destroyed)();

bool32 Rexon_CheckVulnerable(Entity* self) {
	return (
	    ((EntityRexon*)self)->state == Rexon_State_Hidden
	 || ((EntityRexon*)self)->state == Rexon_State_Rising
	 || ((EntityRexon*)self)->state == Rexon_State_Shooting
	);
}

Hitbox* Rexon_GetHitbox(Entity* self) { return &(Rexon->hitboxBadnik); }

void Rexon_OnHit(EntityPlayer* player, Entity* self) {
	int32 velocities[] = { -0x8000, 0x10000, -0x10000, 0x8000 };
	for (int32 i = 1; i < REXON_SEGMENT_COUNT; ++i) {
		EntityRexon* debris = CREATE_ENTITY(Rexon, INT_TO_VOID(REXON_DEBRIS), ((EntityRexon*)self)->positions[i].x, ((EntityRexon*)self)->positions[i].y);
		debris->direction   = self->direction;
		debris->velocity.x  = velocities[(i - 1) & 3];
	}
	((EntityRexon*)self)->state = Rexon_State_Destroyed;
	Generic_BadnikBreak_NoEntity(player, self->position, true);
}

void Rexon_AdjustPos(Entity* self) { self->position = ((EntityRexon*)self)->positions[0]; }

void Rexon_EnemyInfoHook() {
	Mod.Super(Rexon->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Rexon->classID, Rexon_CheckVulnerable, Rexon_GetHitbox, Rexon_OnHit, Rexon_AdjustPos, ATKFLAG_NONE);
}