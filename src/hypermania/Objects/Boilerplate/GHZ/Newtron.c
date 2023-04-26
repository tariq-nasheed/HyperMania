#include "Newtron.h"

ObjectNewtron *Newtron;
void (*Newtron_State_StartFly)(void);
void (*Newtron_State_Fly)(void);
void (*Newtron_State_Shoot)(void);

bool32 Newtron_CheckVulnerable(Entity* self) {
	return (
	    ((EntityNewtron*)self)->state == Newtron_State_StartFly
	 || ((EntityNewtron*)self)->state == Newtron_State_Fly
	 || ((EntityNewtron*)self)->state == Newtron_State_Shoot
	);
}

Hitbox* Newtron_GetHitbox(Entity* self) { return &(Newtron->hitboxShoot); }

void Newtron_EnemyInfoHook(void) {
	Mod.Super(Newtron->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Newtron->classID, Newtron_CheckVulnerable, Newtron_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}