#include "Splats.h"

ObjectSplats *Splats;
void (*Splats_State_BounceAround)(void);
void (*Splats_State_JumpOutOfJar)(void);
void (*Splats_State_HandleBouncing)(void);
void (*Splats_State_HandleLanding)(void);
void (*Splats_State_NoMoreJumps)(void);

void Splats_EnemyInfoHook(void) {
	Mod.Super(Splats->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Splats->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Splats_State_BounceAround;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Splats->hitboxBadnikGHZ;
	EnemyDefs[EnemyInfoSlot].states[1].func = Splats_State_JumpOutOfJar;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Splats->hitboxBadnikGHZ;
	EnemyDefs[EnemyInfoSlot].states[2].func = Splats_State_HandleBouncing;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Splats->hitboxBadnikGHZ;
	EnemyDefs[EnemyInfoSlot].states[3].func = Splats_State_HandleLanding;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &Splats->hitboxBadnikGHZ;
	EnemyDefs[EnemyInfoSlot].states[4].func = Splats_State_NoMoreJumps;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &Splats->hitboxBadnikGHZ;
	EnemyDefs[EnemyInfoSlot].destroy_func = Splats_Destroy;
	++EnemyInfoSlot;
}

void Splats_Destroy(EntityPlayer* player, Entity* e) {
	EntitySplats* self = (EntitySplats*)e;
	if (Splats->initialState != Splats_State_BounceAround) {
		EntitySplats *parent = (EntitySplats*)self->parent;
		if (parent) {
			if (parent->classID == Splats->classID) --parent->activeCount;
		}
	}
	BreakBadnik(player, e);
}