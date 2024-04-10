#include "Canista.h"

ObjectCanista* Canista;
void (*Canista_State_Moving)();
void (*Canista_State_Idle)();

bool32 Canista_CheckVulnerable(Entity* self) {
	return (
	    ((EntityCanista*)self)->state == Canista_State_Moving
	 || ((EntityCanista*)self)->state == Canista_State_Idle
	);
}

Hitbox* Canista_GetHitbox(Entity* self) { return &(Canista->hitboxBadnik); }

void Canista_EnemyInfoHook() {
	Mod.Super(Canista->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Canista->classID, Canista_CheckVulnerable, Canista_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}