#include "Grabber.h"

ObjectGrabber* Grabber;

Hitbox* Grabber_GetHitbox(Entity* self) { return &(Grabber->hitboxBadnik); }

void Grabber_OnHit(EntityPlayer* player, Entity* self) {
	EntityPlayer* playerPtr = ((EntityGrabber*)self)->grabbedPlayer;
	if (playerPtr) playerPtr->state = Player_State_Air;
	Generic_BadnikBreak(player, self, true);
}

void Grabber_EnemyInfoHook() {
	Mod.Super(Grabber->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Grabber->classID, Generic_CheckVulnerable, Grabber_GetHitbox, Grabber_OnHit, NULL, ATKFLAG_NONE);
}