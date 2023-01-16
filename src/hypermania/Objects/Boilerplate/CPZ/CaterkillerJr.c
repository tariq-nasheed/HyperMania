#include "CaterkillerJr.h"

Hitbox hitbox;
ObjectCaterkillerJr *CaterkillerJr;
void (*CaterkillerJr_State_Move)(void);

void CaterkillerJr_EnemyInfoHook(void) {
	hitbox.left   = -8;
	hitbox.top    = -8;
	hitbox.right  = 8;
	hitbox.bottom = 8;
	Mod.Super(CaterkillerJr->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = CaterkillerJr->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = CaterkillerJr_State_Move;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &hitbox;
	EnemyDefs[EnemyInfoSlot].destroy_func = CaterkillerJr_SpawnDebris;
	++EnemyInfoSlot;
}

void CaterkillerJr_SpawnDebris(EntityPlayer* player, Entity* e) {
	BreakBadnik(player, e);
	EntityCaterkillerJr* self = (EntityCaterkillerJr*)e;
	for (int32 i = 1; i < CATERKILLERJR_SEGMENT_COUNT; ++i) {
		EntityDebris *debris    = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, self->bodyPosition[i].x, self->bodyPosition[i].y);
		debris->animator        = self->bodyAnimators[i];
		debris->velocity.x      = RSDK.Rand(-16, 16) << 14;
		debris->velocity.y      = RSDK.Rand(-8, 8) << 14;
		debris->gravityStrength = 0x3800;
		debris->drawGroup       = Zone->objectDrawGroup[0];
		debris->updateRange.x   = 0x400000;
		debris->updateRange.y   = 0x400000;
	}
}