#include "Batbrain.h"

ObjectBatbrain *Batbrain;
void (*Batbrain_State_CheckPlayerInRange)(void);
void (*Batbrain_State_DropToPlayer)(void);
void (*Batbrain_State_Fly)(void);
void (*Batbrain_State_FlyToCeiling)(void);

bool32 Batbrain_CheckVulnerable(Entity* self) {
	return (
	    ((EntityBatbrain*)self)->state == Batbrain_State_CheckPlayerInRange
	 || ((EntityBatbrain*)self)->state == Batbrain_State_DropToPlayer
	 || ((EntityBatbrain*)self)->state == Batbrain_State_Fly
	 || ((EntityBatbrain*)self)->state == Batbrain_State_FlyToCeiling
	);
}

Hitbox* Batbrain_GetHitbox(Entity* self) { return &(Batbrain->hitboxBadnik); }

void Batbrain_EnemyInfoHook(void) {
	Mod.Super(Batbrain->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Batbrain->classID, Batbrain_CheckVulnerable, Batbrain_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}