#include "Rattlekiller.h"

ObjectRattlekiller *Rattlekiller;

Hitbox* Rattlekiller_GetHitbox(Entity* self) { return &(Rattlekiller->hitboxSegment); }

void Rattlekiller_OnHit(EntityPlayer* player, Entity* self) {
	for (int32 i = 1; i < RATTLEKILLER_SEGMENT_COUNT; ++i) {
		EntityDebris *debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, ((EntityRattlekiller*)self)->bodyPositions[i].x, ((EntityRattlekiller*)self)->bodyPositions[i].y);

		RSDK.SetSpriteAnimation(Rattlekiller->aniFrames, ((EntityRattlekiller*)self)->bodyAnimators[i]->animationID, &debris->animator, true,
		                        ((EntityRattlekiller*)self)->bodyAnimators[i]->frameID);
		debris->velocity.x      = RSDK.Rand(-0x20000, 0x20000);
		debris->velocity.y      = RSDK.Rand(-0x20000, -0x10000);
		debris->gravityStrength = 0x4800;
		debris->drawGroup       = Zone->objectDrawGroup[1];
		debris->updateRange.x   = 0x400000;
		debris->updateRange.y   = 0x400000;
	}
	Generic_BadnikBreak(player, self, true);
}

void Rattlekiller_AdjustPos(Entity* self) { self->position = ((EntityRattlekiller*)self)->bodyPositions[0]; }

void Rattlekiller_EnemyInfoHook() {
	Mod.Super(Rattlekiller->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Rattlekiller->classID, Generic_CheckVulnerable, Rattlekiller_GetHitbox, Rattlekiller_OnHit, Rattlekiller_AdjustPos, ATKFLAG_NONE);
}
