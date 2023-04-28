#include "Dango.h"

ObjectDango* Dango;
void (*Dango_State_Walking)();
void (*Dango_State_Turning)();
void (*Dango_State_Falling_Uncurled)();
void (*Dango_State_Curling)();
void (*Dango_State_Rolling)();
void (*Dango_State_Falling_Curled)();
void (*Dango_State_Uncurling)();

bool32 Dango_CheckVulnerable(Entity* self) {
	return (
	    ((EntityDango*)self)->state == Dango_State_Walking
	 || ((EntityDango*)self)->state == Dango_State_Turning
	 || ((EntityDango*)self)->state == Dango_State_Falling_Uncurled
	 || ((EntityDango*)self)->state == Dango_State_Curling
	 || ((EntityDango*)self)->state == Dango_State_Rolling
	 || ((EntityDango*)self)->state == Dango_State_Falling_Curled
	 || ((EntityDango*)self)->state == Dango_State_Uncurling
	);
}

Hitbox* Dango_GetHitbox(Entity* self) { return &(Dango->hitboxBadnik); }

void Dango_EnemyInfoHook() {
	Mod.Super(Dango->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Dango->classID, Dango_CheckVulnerable, Dango_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}