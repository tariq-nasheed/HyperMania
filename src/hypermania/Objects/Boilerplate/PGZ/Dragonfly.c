#include "Dragonfly.h"

ObjectDragonfly *Dragonfly;
void (*Dragonfly_State_Move)(void);

void Dragonfly_EnemyInfoHook(void) {
	Mod.Super(Dragonfly->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Dragonfly->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Dragonfly_State_Move;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Dragonfly->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].destroy_func = Dragonfly_SpawnDebris;
	++EnemyInfoSlot;
}

void Dragonfly_SpawnDebris(EntityPlayer* player, Entity* e) {
	EntityDragonfly* self = (EntityDragonfly*)e;
	for (int32 i = 0; i < DRAGONFLY_SPINE_COUNT; ++i) {
		EntityDragonfly* child  = CREATE_ENTITY(Dragonfly, INT_TO_VOID(true), self->positions[i].x, self->positions[i].y);
		child->animator.frameID = i == 0;
		child->velocity.x       = RSDK.Rand(-4, 4) << 15;
		child->velocity.y       = RSDK.Rand(-5, 1) << 15;
	}
	BreakBadnik(player, e);
}