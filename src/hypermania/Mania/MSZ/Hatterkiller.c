#include "Hatterkiller.h"

ObjectHatterkiller* Hatterkiller;

bool32 Hatterkiller_CheckVulnerable(Entity* self) { return (!HeavyMystic->curtainLinePos); }

Hitbox* Hatterkiller_GetHitbox(Entity* self) { return &(Hatterkiller->hitboxSegment); }

void Hatterkiller_OnHit(EntityPlayer* player, Entity* self) {
	for (int32 i = 1; i < HATTERKILLER_SEGMENT_COUNT; ++i) {
		EntityDebris *debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, ((EntityHatterkiller*)self)->bodyPositions[i].x, ((EntityHatterkiller*)self)->bodyPositions[i].y);

		RSDK.SetSpriteAnimation(Hatterkiller->aniFrames, ((EntityHatterkiller*)self)->bodyAnimators[i]->animationID, &debris->animator, true,
		                        ((EntityHatterkiller*)self)->bodyAnimators[i]->frameID);
		debris->velocity.x      = RSDK.Rand(-0x20000, 0x20000);
		debris->velocity.y      = RSDK.Rand(-0x20000, -0x10000);
		debris->gravityStrength = 0x4800;
		debris->drawGroup       = Zone->objectDrawGroup[1];
		debris->updateRange.x   = 0x400000;
		debris->updateRange.y   = 0x400000;
	}
	Generic_BadnikBreak(player, self, true);
}

void Hatterkiller_AdjustPos(Entity* self) { self->position = ((EntityHatterkiller*)self)->bodyPositions[0]; }

void Hatterkiller_EnemyInfoHook() {
	Mod.Super(Hatterkiller->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Hatterkiller->classID, Hatterkiller_CheckVulnerable, Hatterkiller_GetHitbox, Hatterkiller_OnHit, Hatterkiller_AdjustPos, ATKFLAG_NONE);
}