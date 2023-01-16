#include "Jellygnite.h"

ObjectJellygnite *Jellygnite;
void (*Jellygnite_State_Swimming)(void);
void (*Jellygnite_State_GrabbedPlayer)(void);

void Jellygnite_EnemyInfoHook(void) {
	Mod.Super(Jellygnite->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Jellygnite->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Jellygnite_State_Swimming;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Jellygnite->hitbox;
	EnemyDefs[EnemyInfoSlot].states[1].func = Jellygnite_State_GrabbedPlayer;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Jellygnite->hitbox;
	EnemyDefs[EnemyInfoSlot].destroy_func = Jellygnite_Destroy;
	++EnemyInfoSlot;
}

void Jellygnite_Destroy(EntityPlayer* player, Entity* e) {
	EntityJellygnite* self = (EntityJellygnite*)e;
	if (self->grabbedPlayer && player != self->grabbedPlayer) {
		self->grabbedPlayer->state = Player_State_Air;
	}
	BreakBadnik(player, e);
}