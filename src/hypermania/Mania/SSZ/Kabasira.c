#include "Kabasira.h"

ObjectKabasira* Kabasira;
void (*Kabasira_State_Moving)();

bool32 Kabasira_CheckVulnerable(Entity* self) {
	return (((EntityKabasira*)self)->state == Kabasira_State_Moving);
}

Hitbox* Kabasira_GetHitbox(Entity* self) { return &(Kabasira->hitboxBadnik); }

void Kabasira_EnemyInfoHook() {
	Mod.Super(Kabasira->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Kabasira->classID, Kabasira_CheckVulnerable, Kabasira_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}