#include "Crabmeat.h"

ObjectCrabmeat *Crabmeat;
void (*Crabmeat_State_Projectile)(void);


bool32 Crabmeat_CheckVulnerable(Entity* self) {
	return (((EntityCrabmeat*)self)->state != Crabmeat_State_Projectile);
}

Hitbox* Crabmeat_GetHitbox(Entity* self) { return &(Crabmeat->hitboxBadnik); }

void Crabmeat_EnemyInfoHook(void) {
	Mod.Super(Crabmeat->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Crabmeat->classID, Crabmeat_CheckVulnerable, Crabmeat_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}