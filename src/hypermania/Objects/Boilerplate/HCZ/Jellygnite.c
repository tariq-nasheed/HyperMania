#include "Jellygnite.h"

ObjectJellygnite* Jellygnite;
void (*Jellygnite_State_Init)();

bool32 Jellygnite_CheckVulnerable(Entity* self) {
	return (((EntityJellygnite*)self)->state != Jellygnite_State_Init && self->classID == Jellygnite->classID);
}

Hitbox* Jellygnite_GetHitbox(Entity* self) { return &(Jellygnite->hitbox); }

void Jellygnite_OnHit(EntityPlayer* player, Entity* self) {
	if (((EntityJellygnite*)self)->grabbedPlayer && player != ((EntityJellygnite*)self)->grabbedPlayer) {
		((EntityJellygnite*)self)->grabbedPlayer->state = Player_State_Air;
	}
	Generic_BadnikBreak(player, self, true);
}

void Jellygnite_EnemyInfoHook() {
	Mod.Super(Jellygnite->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Jellygnite->classID, Jellygnite_CheckVulnerable, Jellygnite_GetHitbox, Jellygnite_OnHit, NULL, ATKFLAG_NONE);
}