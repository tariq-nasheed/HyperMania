#include "Woodrow.h"

ObjectWoodrow *Woodrow;
void (*Woodrow_State_Idle)();
void (*Woodrow_State_MoveUp)();
void (*Woodrow_State_MoveDown)();

bool32 Woodrow_CheckVulnerable(Entity* self) {
	return (
	    ((EntityWoodrow*)self)->state == Woodrow_State_Idle
	 || ((EntityWoodrow*)self)->state == Woodrow_State_MoveUp
	 || ((EntityWoodrow*)self)->state == Woodrow_State_MoveDown
	);
}

Hitbox* Woodrow_GetHitbox(Entity* self) { return &(Woodrow->hitboxBadnik); }

void Woodrow_EnemyInfoHook() {
	Mod.Super(Woodrow->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Woodrow->classID, Woodrow_CheckVulnerable, Woodrow_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}
