#include "Jawz.h"

ObjectJawz* Jawz;
void (*Jawz_State_Triggered)();

bool32 Jawz_CheckVulnerable(Entity* self) {
	return (
	    ((EntityJawz*)self)->state == Jawz_State_Triggered
	);
}

Hitbox* Jawz_GetHitbox(Entity* self) { return &(Jawz->hitboxBadnik); }

void Jawz_EnemyInfoHook() {
	Mod.Super(Jawz->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Jawz->classID, Jawz_CheckVulnerable, Jawz_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}
