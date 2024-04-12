#include "Scarab.h"

ObjectScarab* Scarab;
void (*Scarab_HandlePlayerRelease)();

Hitbox* Scarab_GetHitbox(Entity* self) { return &(Scarab->hitboxBadnik); }

void Scarab_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	Scarab_HandlePlayerRelease();
	SceneInfo->entity = old_entity;
	Generic_BadnikBreak(player, self, true);
}

void Scarab_EnemyInfoHook() {
	Mod.Super(Scarab->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Scarab->classID, Generic_CheckVulnerable, Scarab_GetHitbox, Scarab_OnHit, NULL, ATKFLAG_NONE);
}