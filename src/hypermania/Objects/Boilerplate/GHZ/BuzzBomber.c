#include "BuzzBomber.h"

ObjectBuzzBomber* BuzzBomber;
void (*BuzzBomber_State_Flying)();
void (*BuzzBomber_State_Idle)();
void (*BuzzBomber_State_DetectedPlayer)();

bool32 BuzzBomber_CheckVulnerable(Entity* self) {
	return (
	    ((EntityBuzzBomber*)self)->state == BuzzBomber_State_Flying
	 || ((EntityBuzzBomber*)self)->state == BuzzBomber_State_Idle
	 || ((EntityBuzzBomber*)self)->state == BuzzBomber_State_DetectedPlayer
	);
}

Hitbox* BuzzBomber_GetHitbox(Entity* self) { return &(BuzzBomber->hitboxBadnik); }

void BuzzBomber_OnHit(EntityPlayer* player, Entity* self) {
	if (((EntityBuzzBomber*)self)->projectile) destroyEntity(((EntityBuzzBomber*)self)->projectile);
	Generic_BadnikBreak(player, self, true);
}

void BuzzBomber_EnemyInfoHook() {
	Mod.Super(BuzzBomber->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(BuzzBomber->classID, BuzzBomber_CheckVulnerable, BuzzBomber_GetHitbox, BuzzBomber_OnHit, NULL, ATKFLAG_NONE);
}