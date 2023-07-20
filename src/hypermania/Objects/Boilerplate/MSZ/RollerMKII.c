#include "RollerMKII.h"

ObjectRollerMKII* RollerMKII;
void (*RollerMKII_State_Idle)();
void (*RollerMKII_State_SpinUp)();

bool32 RollerMKII_CheckVulnerable(Entity* self) {
	return (
	    ((EntityRollerMKII*)self)->state == RollerMKII_State_Idle
	 || ((EntityRollerMKII*)self)->state == RollerMKII_State_SpinUp
	);
}

Hitbox* RollerMKII_GetHitbox(Entity* self) { return &(RollerMKII->hitboxBadnik); }

void RollerMKII_EnemyInfoHook() {
	Mod.Super(RollerMKII->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(RollerMKII->classID, RollerMKII_CheckVulnerable, RollerMKII_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}
