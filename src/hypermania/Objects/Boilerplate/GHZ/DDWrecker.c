#include "DDWrecker.h"

ObjectDDWrecker *DDWrecker;
void (*DDWrecker_StateBall_Vulnerable)(void);
void (*DDWrecker_StateBall_Spiked)(void);
void (*DDWrecker_StateBall_Partnerless)(void);
void (*DDWrecker_Hit)(void);

bool32 DDWrecker_CheckVulnerable(Entity* self) {
	if (((EntityDDWrecker*)self)->invincibilityTimer) return false;
	return (
	    ((EntityDDWrecker*)self)->stateBall == DDWrecker_StateBall_Vulnerable
	 || ((EntityDDWrecker*)self)->stateBall == DDWrecker_StateBall_Spiked
	 || ((EntityDDWrecker*)self)->stateBall == DDWrecker_StateBall_Partnerless
	);
}

Hitbox* DDWrecker_GetHitbox(Entity* self) { return &(((EntityDDWrecker*)self)->hitbox); }

void DDWrecker_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	DDWrecker_Hit();
	SceneInfo->entity = old_entity;
}

void DDWrecker_EnemyInfoHook(void) {
	Mod.Super(DDWrecker->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(DDWrecker->classID, DDWrecker_CheckVulnerable, DDWrecker_GetHitbox, DDWrecker_OnHit, NULL, ATKFLAG_ISBOSS);
}