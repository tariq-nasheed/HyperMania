#include "Tubinaut.h"

ObjectTubinaut* Tubinaut;
void (*Tubinaut_State_Move)();

Hitbox* Tubinaut_GetHitbox(Entity* self) { return &(Tubinaut->hitboxFace); }

bool32 Tubinaut_CheckVulnerable(Entity* self) {
	return (((EntityTubinaut*)self)->state == Tubinaut_State_Move);
}

void Tubinaut_OnHit(EntityPlayer* player, Entity* self) {
	for (int32 i = 0; i < TUBINAUT_ORB_COUNT; ++i) {
		if (((EntityTubinaut*)self)->ballsVisible[i]) {
			EntityTubinaut* orb = CREATE_ENTITY(Tubinaut, INT_TO_VOID(i + 1), ((EntityTubinaut*)self)->orbPositions[i].x, ((EntityTubinaut*)self)->orbPositions[i].y);
			orb->velocity.x     = 0x380 * RSDK.Cos256(((EntityTubinaut*)self)->orbAngles[i] >> 4);
			orb->velocity.y     = 0x380 * RSDK.Sin256(((EntityTubinaut*)self)->orbAngles[i] >> 4);
		}
	}
	Generic_BadnikBreak(player, self, true);
}

void Tubinaut_EnemyInfoHook() {
	Mod.Super(Tubinaut->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Tubinaut->classID, Tubinaut_CheckVulnerable, Tubinaut_GetHitbox, Tubinaut_OnHit, NULL, ATKFLAG_NONE);
}