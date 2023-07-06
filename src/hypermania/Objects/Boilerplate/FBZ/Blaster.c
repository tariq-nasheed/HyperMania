#include "Blaster.h"

ObjectBlaster* Blaster;
void (*Blaster_State_BeginShot)();
void (*Blaster_State_Shot)();
void (*Blaster_State_Shell)();

bool32 Blaster_CheckVulnerable(Entity* self) {
	return (
	    ((EntityBlaster*)self)->state != Blaster_State_BeginShot
	 && ((EntityBlaster*)self)->state != Blaster_State_Shot
	 && ((EntityBlaster*)self)->state != Blaster_State_Shell
	);
}

Hitbox* Blaster_GetHitbox(Entity* self) { return &(Blaster->hitboxBadnik); }

void Blaster_EnemyInfoHook() {
	Mod.Super(Blaster->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Blaster->classID, Blaster_CheckVulnerable, Blaster_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}