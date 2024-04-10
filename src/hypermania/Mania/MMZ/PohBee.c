#include "PohBee.h"

ObjectPohBee* PohBee;

Hitbox* PohBee_GetHitbox(Entity* self) { return &(PohBee->hitbox); }

void PohBee_OnHit(EntityPlayer* player, Entity* self) {
	if (self->drawGroup == 1) {
		RSDK.PlaySfx(Explosion->sfxDestroy, false, 255);
		CREATE_ENTITY(Explosion, INT_TO_VOID(EXPLOSION_ENEMY), self->position.x, self->position.y)->drawGroup = 1;
		destroyEntity(self);
	} else {
		Generic_BadnikBreak(player, self, true);
	}
}

void PohBee_EnemyInfoHook() {
	Mod.Super(PohBee->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(PohBee->classID, Generic_CheckVulnerable, PohBee_GetHitbox, PohBee_OnHit, NULL, ATKFLAG_NONE);
}