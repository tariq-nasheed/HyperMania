#include "GigaMetal.h"
#if MANIA_USE_PLUS

ObjectGigaMetal* GigaMetal;
void (*GigaMetal_StateBody_Marching)();
void (*GigaMetal_Hit)();

bool32 GigaMetal_CheckVulnerable(Entity* self) {
	if (GigaMetal->invincibleTimer) return false;
	return (((EntityGigaMetal*)self)->state == GigaMetal_StateBody_Marching);
}

Hitbox* GigaMetal_GetHitbox(Entity* self) { return &(GigaMetal->hitboxCore); }

void GigaMetal_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	GigaMetal_Hit();
	SceneInfo->entity = old_entity;
}

void GigaMetal_EnemyInfoHook() {
	Mod.Super(GigaMetal->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(GigaMetal->classID, GigaMetal_CheckVulnerable, GigaMetal_GetHitbox, GigaMetal_OnHit, NULL, ATKFLAG_ISBOSS);
}

#endif