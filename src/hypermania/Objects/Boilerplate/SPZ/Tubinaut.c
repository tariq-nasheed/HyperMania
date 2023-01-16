#include "Tubinaut.h"

ObjectTubinaut *Tubinaut;
void (*Tubinaut_State_Move)(void);

void Tubinaut_EnemyInfoHook(void) {
	Mod.Super(Tubinaut->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Tubinaut->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Tubinaut_State_Move;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Tubinaut->hitboxFace;
	EnemyDefs[EnemyInfoSlot].destroy_func = Tubinaut_SpawnBalls;
	++EnemyInfoSlot;
}

void Tubinaut_SpawnBalls(EntityPlayer* player, Entity* e) {
	BreakBadnik(player, e);
	EntityTubinaut* self = (EntityTubinaut*)e;
	for (int32 i = 0; i < TUBINAUT_ORB_COUNT; ++i) {
		if (self->ballsVisible[i]) {
			EntityTubinaut* orb = CREATE_ENTITY(Tubinaut, INT_TO_VOID(i + 1), self->orbPositions[i].x, self->orbPositions[i].y);
			orb->velocity.x     = 0x380 * RSDK.Cos256(self->orbAngles[i] >> 4);
			orb->velocity.y     = 0x380 * RSDK.Sin256(self->orbAngles[i] >> 4);
		}
	}
}