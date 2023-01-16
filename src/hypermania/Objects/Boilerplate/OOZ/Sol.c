#include "Sol.h"

ObjectSol *Sol;
void (*Sol_State_Moving)(void);
void (*Sol_State_ShootingOrbs)(void);
void (*Sol_State_NoOrbs)(void);
void (*Sol_State_ActiveFireball)(void);

void Sol_EnemyInfoHook(void) {
	Mod.Super(Sol->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Sol->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Sol_State_Moving;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Sol->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Sol_State_ShootingOrbs;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Sol->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Sol_State_NoOrbs;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Sol->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].destroy_func = Sol_DropHotBalls;
	++EnemyInfoSlot;
}

void Sol_DropHotBalls(EntityPlayer* player, Entity* e) {
	EntitySol* self = (EntitySol*)e;
	int32 angle = self->angle;
	for (int32 i = 0; i < SOL_FLAMEORB_COUNT; ++i) {
		if ((1 << i) & self->activeOrbs) {
			self->position.x = self->positions[i].x;
			self->position.y = self->positions[i].y;

			EntitySol *sol = CREATE_ENTITY(Sol, INT_TO_VOID(true), self->positions[i].x, self->positions[i].y);

			sol->state = Sol_State_ActiveFireball;
			sol->velocity.x = 0x380 * RSDK.Cos256(angle);
			sol->velocity.y = 0x380 * RSDK.Sin256(angle);
		}
		angle += (0x100 / SOL_FLAMEORB_COUNT);
	}

	BreakBadnik(player, e);
}