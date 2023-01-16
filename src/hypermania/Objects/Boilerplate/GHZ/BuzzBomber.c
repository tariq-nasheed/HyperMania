#include "BuzzBomber.h"

ObjectBuzzBomber *BuzzBomber;
void (*BuzzBomber_State_Flying)(void);
void (*BuzzBomber_State_Idle)(void);
void (*BuzzBomber_State_DetectedPlayer)(void);

void BuzzBomber_EnemyInfoHook(void) {
	Mod.Super(BuzzBomber->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = BuzzBomber->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = BuzzBomber_State_Flying;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &BuzzBomber->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = BuzzBomber_State_Idle;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &BuzzBomber->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = BuzzBomber_State_DetectedPlayer;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &BuzzBomber->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].destroy_func = BuzzBomber_DestroyProjectile;
	++EnemyInfoSlot;
}

void BuzzBomber_DestroyProjectile(EntityPlayer* player, Entity* e) {
	EntityBuzzBomber* self = (EntityBuzzBomber*)e;
	if (self->projectile) destroyEntity(self->projectile);
	BreakBadnik(player, e);
}