#include "CaterkillerJr.h"

ObjectCaterkillerJr* CaterkillerJr;
Hitbox hitbox;

Hitbox* CaterkillerJr_GetHitbox(Entity* self) { return &hitbox; }

void CaterkillerJr_OnHit(EntityPlayer* player, Entity* self) {
	for (int32 i = 1; i < CATERKILLERJR_SEGMENT_COUNT; ++i) {
		EntityDebris* debris    = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, ((EntityCaterkillerJr*)self)->bodyPosition[i].x, ((EntityCaterkillerJr*)self)->bodyPosition[i].y);
		debris->animator        = ((EntityCaterkillerJr*)self)->bodyAnimators[i];
		debris->velocity.x      = RSDK.Rand(-16, 16) << 14;
		debris->velocity.y      = RSDK.Rand(-8, 8) << 14;
		debris->gravityStrength = 0x3800;
		debris->drawGroup       = Zone->objectDrawGroup[0];
		debris->updateRange.x   = 0x400000;
		debris->updateRange.y   = 0x400000;
	}
	Generic_BadnikBreak(player, self, true);
}

void CaterkillerJr_AdjustPos(Entity* self) { self->position = ((EntityCaterkillerJr*)self)->bodyPosition[0]; }

void CaterkillerJr_EnemyInfoHook() {
	// catterkiller jr has a weird lopsided hitbox that makes collision with super flickies unreliable so we define our own instead
	hitbox.left   = -8;
	hitbox.top    = -8;
	hitbox.right  = 8;
	hitbox.bottom = 8;
	Mod.Super(CaterkillerJr->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(CaterkillerJr->classID, Generic_CheckVulnerable, CaterkillerJr_GetHitbox, CaterkillerJr_OnHit, CaterkillerJr_AdjustPos, ATKFLAG_NONE);
}