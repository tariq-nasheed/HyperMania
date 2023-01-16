#include "Fireworm.h"

ObjectFireworm *Fireworm;
void (*Fireworm_State_FlyAround)(void);

void Fireworm_EnemyInfoHook(void) {
	Mod.Super(Fireworm->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Fireworm->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Fireworm_State_FlyAround;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Fireworm->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].destroy_func = Fireworm_SpawnDebris;
	++EnemyInfoSlot;
}

void Fireworm_SpawnDebris(EntityPlayer* player, Entity* e) {
	EntityFireworm* self = (EntityFireworm*)e;

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

	for (int32 i = 1; i < FIREWORM_SEGMENT_COUNT; ++i) {
		EntityDebris *debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, self->bodyPositions[i].x, self->bodyPositions[i].y);
		RSDK.SetSpriteAnimation(Fireworm->aniFrames, 3, &debris->animator, true, 0);
		debris->velocity.x      = RSDK.Rand(-0x40000, 0x40000);
		debris->velocity.y      = RSDK.Rand(-0x40000, 0x40000);
		debris->gravityStrength = 0x3800;
		debris->drawGroup       = Zone->objectDrawGroup[0];
		debris->updateRange.x   = 0x400000;
		debris->updateRange.y   = 0x400000;
	}
	self->state = StateMachine_None;
}