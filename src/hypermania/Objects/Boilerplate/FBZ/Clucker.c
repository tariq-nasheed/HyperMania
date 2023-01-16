#include "Clucker.h"

ObjectClucker *Clucker;
void (*Clucker_State_Appear)(void);
void (*Clucker_State_ShootDelay)(void);
void (*Clucker_State_Shoot)(void);
void (*Clucker_State_Turn)(void);
void (*Clucker_State_Destroyed)(void);

void Clucker_EnemyInfoHook(void) {
	Mod.Super(Clucker->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Clucker->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Clucker_State_Appear;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Clucker->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Clucker_State_ShootDelay;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Clucker->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Clucker_State_Shoot;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Clucker->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = Clucker_State_Turn;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &Clucker->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].destroy_func = Clucker_DestroyPilot;
	++EnemyInfoSlot;
}

void Clucker_DestroyPilot(EntityPlayer* player, Entity* e) {
	EntityClucker* self = (EntityClucker*)e;
	int32 posY = self->position.y;
	if ((self->direction & FLIP_Y)) self->position.y -= self->yOffset;
	else self->position.y += self->yOffset;
	if (self->hasParent) {
		BreakBadnik(player, e);
	} else {
		CREATE_ENTITY(Animals, INT_TO_VOID((Animals->animalTypes[(RSDK.Rand(0, 32) >> 4)]) + 1), self->position.x, self->position.y);
		EntityExplosion *explosion = CREATE_ENTITY(Explosion, INT_TO_VOID(EXPLOSION_ENEMY), self->position.x, self->position.y);
		explosion->drawGroup       = Zone->objectDrawGroup[1];
		RSDK.PlaySfx(Explosion->sfxDestroy, false, 255);
		EntityScoreBonus* scoreBonus = CREATE_ENTITY(ScoreBonus, NULL, self->position.x, self->position.y);
		scoreBonus->drawGroup        = Zone->objectDrawGroup[1];
		scoreBonus->animator.frameID = player->scoreBonus;

		if (globals->gameMode != MODE_COMPETITION) player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
		switch (player->scoreBonus) {
			case 0: Player_GiveScore(player, 100); break;
			case 1: Player_GiveScore(player, 200); break;
			case 2: Player_GiveScore(player, 500); break;
			case 14: Player_GiveScore(player, 1000); break;
			case 15: Player_GiveScore(player, 10000); break;
			default: break;
		}
		if (player->scoreBonus < 15) player->scoreBonus++;

		self->yOffset    = -0x7FFFFFFF;
		self->state      = Clucker_State_Destroyed;
	}
	self->position.y = posY;
}