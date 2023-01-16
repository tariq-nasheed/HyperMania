#include "PohBee.h"

ObjectPohBee *PohBee;

void PohBee_EnemyInfoHook(void) {
	Mod.Super(PohBee->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = PohBee->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &PohBee->hitbox;
	EnemyDefs[EnemyInfoSlot].destroy_func = PohBee_Destroy;
	++EnemyInfoSlot;
}

void PohBee_Destroy(EntityPlayer* player, Entity* e) {
	EntityPohBee* self = (EntityPohBee*)e;
	if (self->drawGroup == 1) {
		CREATE_ENTITY(Explosion, INT_TO_VOID(EXPLOSION_ENEMY), self->position.x, self->position.y)->drawGroup = 1;
	}
	BreakBadnik(player, e);
}