#include "Technosqueek.h"

ObjectTechnosqueek* Technosqueek;

Hitbox* Technosqueek_GetHitbox(Entity* self) { return &(Technosqueek->hitboxBadnik); }

void Technosqueek_EnemyInfoHook() {
	Mod.Super(Technosqueek->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Technosqueek->classID, Generic_CheckVulnerable, Technosqueek_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}