#include "Aquis.h"

ObjectAquis* Aquis;
void (*Aquis_State_Shot)();

bool32 Aquis_CheckVulnerable(Entity* self) {
	return (((EntityAquis*)self)->state != Aquis_State_Shot);
}

Hitbox* Aquis_GetHitbox(Entity* self) { return &(Aquis->hitboxBadnik); }

void Aquis_EnemyInfoHook() {
	Mod.Super(Aquis->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Aquis->classID, Aquis_CheckVulnerable, Aquis_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}
