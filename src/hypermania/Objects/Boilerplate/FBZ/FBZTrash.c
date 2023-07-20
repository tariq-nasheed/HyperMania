#include "FBZTrash.h"

ObjectFBZTrash* FBZTrash;
void (*FBZTrash_State_OrbinautMove)();

bool32 FBZTrash_CheckVulnerable(Entity* self) {
	return (((EntityFBZTrash*)self)->state == FBZTrash_State_OrbinautMove);
}

Hitbox* FBZTrash_GetHitbox(Entity* self) { return &(((EntityFBZTrash*)self)->hitbox); }

void FBZTrash_OnHit(EntityPlayer* player, Entity* self) {
	Generic_BadnikBreak(player, self, false);
	// shitty hack to avoid dangling orbs (didn't happen with old system for some reason)
	foreach_all(FBZTrash, trash) {
		if (trash->parent == self) destroyEntity(trash);
	}
}

void FBZTrash_EnemyInfoHook() {
	Mod.Super(FBZTrash->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(FBZTrash->classID, FBZTrash_CheckVulnerable, FBZTrash_GetHitbox, FBZTrash_OnHit, NULL, ATKFLAG_NONE);
}
