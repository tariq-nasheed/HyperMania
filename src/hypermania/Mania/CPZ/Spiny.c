#include "Spiny.h"

ObjectSpiny* Spiny;
void (*Spiny_State_Shot)();
void (*Spiny_State_ShotDisappear)();

bool32 Spiny_CheckVulnerable(Entity* self) {
	return (
	    ((EntitySpiny*)self)->state != Spiny_State_Shot
	 && ((EntitySpiny*)self)->state != Spiny_State_ShotDisappear
	);
}

Hitbox* Spiny_GetHitbox(Entity* self) { return &(Spiny->hitboxSpiny); }

void Spiny_EnemyInfoHook() {
	Mod.Super(Spiny->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Spiny->classID, Spiny_CheckVulnerable, Spiny_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}