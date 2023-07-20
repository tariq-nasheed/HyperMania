#include "Sol.h"

ObjectSol* Sol;
void (*Sol_State_Moving)();
void (*Sol_State_ShootingOrbs)();
void (*Sol_State_NoOrbs)();
void (*Sol_State_ActiveFireball)();

bool32 Sol_CheckVulnerable(Entity* self) {
	return (
	    ((EntitySol*)self)->state == Sol_State_Moving
	 || ((EntitySol*)self)->state == Sol_State_ShootingOrbs
	 || ((EntitySol*)self)->state == Sol_State_NoOrbs
	);
}

Hitbox* Sol_GetHitbox(Entity* self) { return &(Sol->hitboxBadnik); }

void Sol_OnHit(EntityPlayer* player, Entity* self) {
	Generic_BadnikBreak(player, self, true);
	int32 angle = self->angle;
	for (int32 i = 0; i < SOL_FLAMEORB_COUNT; ++i) {
		if ((1 << i) & ((EntitySol*)self)->activeOrbs) {
			self->position.x = ((EntitySol*)self)->positions[i].x;
			self->position.y = ((EntitySol*)self)->positions[i].y;

			EntitySol* sol = CREATE_ENTITY(Sol, INT_TO_VOID(true), ((EntitySol*)self)->positions[i].x, ((EntitySol*)self)->positions[i].y);

			sol->state = Sol_State_ActiveFireball;
			sol->velocity.x = 0x380*  RSDK.Cos256(angle);
			sol->velocity.y = 0x380*  RSDK.Sin256(angle);
		}
		angle += (0x100 / SOL_FLAMEORB_COUNT);
	}
}

void Sol_EnemyInfoHook() {
	Mod.Super(Sol->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Sol->classID, Sol_CheckVulnerable, Sol_GetHitbox, Sol_OnHit, NULL, ATKFLAG_NONE);
}