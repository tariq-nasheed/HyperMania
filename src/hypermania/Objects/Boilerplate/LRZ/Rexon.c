#include "Rexon.h"

ObjectRexon *Rexon;
void (*Rexon_State_Hidden)(void);
void (*Rexon_State_Rising)(void);
void (*Rexon_State_Shooting)(void);
void (*Rexon_State_Destroyed)(void);
void (*Rexon_State_Explode)(void);

void Rexon_EnemyInfoHook(void) {
	Mod.Super(Rexon->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Rexon->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Rexon_State_Hidden;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Rexon->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Rexon_State_Rising;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Rexon->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Rexon_State_Shooting;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Rexon->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].destroy_func = Rexon_Destroy;
	++EnemyInfoSlot;
}

void Rexon_Destroy(EntityPlayer* player, Entity* e) {
	EntityRexon* self = (EntityRexon*)e;
	if (self->state != Rexon_State_Destroyed && self->state != Rexon_State_Explode) {
		int32 x = self->position.x;
		int32 y = self->position.y;

		self->position.x = self->positions[0].x;
		self->position.y = self->positions[0].y;

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

		self->position.x = x;
		self->position.y = y;

		int32 velocities[] = { -0x8000, 0x10000, -0x10000, 0x8000 };
		for (int32 i = 1; i < REXON_SEGMENT_COUNT; ++i) {
			EntityRexon *debris = CREATE_ENTITY(Rexon, INT_TO_VOID(REXON_DEBRIS), self->positions[i].x, self->positions[i].y);
			debris->direction   = self->direction;
			debris->velocity.x  = velocities[(i - 1) & 3];
		}
	}
	self->state = Rexon_State_Destroyed;
}