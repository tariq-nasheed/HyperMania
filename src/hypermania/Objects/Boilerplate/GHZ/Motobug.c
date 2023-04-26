#include "Motobug.h"

ObjectMotobug *Motobug;
void (*Motobug_State_Smoke)(void);

bool32 Motobug_CheckVulnerable(Entity* self) {
	return (((EntityMotobug*)self)->state != Motobug_State_Smoke);
}

Hitbox* Motobug_GetHitbox(Entity* self) { return &(Motobug->hitboxBadnik); }

void Motobug_EnemyInfoHook(void) {
	Mod.Super(Motobug->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Motobug->classID, Motobug_CheckVulnerable, Motobug_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}