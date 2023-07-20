#include "Armadiloid.h"

ObjectArmadiloid *Armadiloid;
void (*Armadiloid_State_Rider)();

bool32 Armadiloid_CheckVulnerable(Entity* self) {
	return (((EntityArmadiloid*)self)->state == Armadiloid_State_Rider);
}

Hitbox* Armadiloid_GetHitbox(Entity* self) { return &(((EntityArmadiloid*)self)->hitbox); }

void Armadiloid_OnHit(EntityPlayer* player, Entity* self) {
	EntityArmadiloid* child = (EntityArmadiloid*)(((EntityArmadiloid*)self)->child);
	if (child) child->parent = NULL;
	Generic_BadnikBreak(player, self, true);
}

void Armadiloid_AdjustPos(Entity* self) {
	EntityArmadiloid* child = (EntityArmadiloid*)(((EntityArmadiloid*)self)->child);
	if (child) self->position = child->position;
}

void Armadiloid_EnemyInfoHook() {
	Mod.Super(Armadiloid->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Armadiloid->classID, Armadiloid_CheckVulnerable, Armadiloid_GetHitbox, Armadiloid_OnHit, Armadiloid_AdjustPos, ATKFLAG_NONE);
}