#include "Dragonfly.h"

ObjectDragonfly* Dragonfly;
void (*Dragonfly_State_Move)();

bool32 Dragonfly_CheckVulnerable(Entity* self) {
	return (((EntityDragonfly*)self)->state == Dragonfly_State_Move);
}

Hitbox* Dragonfly_GetHitbox(Entity* self) { return &(Dragonfly->hitboxBadnik); }

void Dragonfly_OnHit(EntityPlayer* player, Entity* self) {
	for (int32 i = 0; i < DRAGONFLY_SPINE_COUNT; ++i) {
		EntityDragonfly* child  = CREATE_ENTITY(Dragonfly, INT_TO_VOID(true), ((EntityDragonfly*)self)->positions[i].x, ((EntityDragonfly*)self)->positions[i].y);
		child->animator.frameID = (i == 0);
		child->velocity.x       = RSDK.Rand(-4, 4) << 15;
		child->velocity.y       = RSDK.Rand(-5, 1) << 15;
	}
	Generic_BadnikBreak(player, self, true);
}

void Dragonfly_EnemyInfoHook() {
	Mod.Super(Dragonfly->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Dragonfly->classID, Dragonfly_CheckVulnerable, Dragonfly_GetHitbox, Dragonfly_OnHit, NULL, ATKFLAG_NONE);
}