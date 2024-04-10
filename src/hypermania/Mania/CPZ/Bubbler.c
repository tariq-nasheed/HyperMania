#include "Bubbler.h"

ObjectBubbler* Bubbler;
void (*Bubbler_StateProjectile_Seed)();
void (*Bubbler_StateProjectile_Bubbler)();

bool32 Bubbler_CheckVulnerable(Entity* self) {
	return (
	    ((EntityBubbler*)self)->state != Bubbler_StateProjectile_Seed
	 && ((EntityBubbler*)self)->state != Bubbler_StateProjectile_Bubbler
	);
}

Hitbox* Bubbler_GetHitbox(Entity* self) { return &(Bubbler->hitboxBadnik); }

void Bubbler_EnemyInfoHook() {
	Mod.Super(Bubbler->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Bubbler->classID, Bubbler_CheckVulnerable, Bubbler_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}