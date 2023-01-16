#include "Hatterkiller.h"

ObjectHatterkiller *Hatterkiller;

void Hatterkiller_EnemyInfoHook(void) {
	Mod.Super(Hatterkiller->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Hatterkiller->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].destroy_func = Hatterkiller_SpawnDebris;
	++EnemyInfoSlot;
}

void Hatterkiller_SpawnDebris(EntityPlayer* player, Entity* e) {
	EntityHatterkiller* self = (EntityHatterkiller*)e;
	for (int32 s = 1; s < HATTERKILLER_SEGMENT_COUNT; ++s) {
		Vector2 *position    = &self->bodyPositions[s];
		Animator *animator   = self->bodyAnimators[s];
		EntityDebris *debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, position->x, position->y);

		RSDK.SetSpriteAnimation(Hatterkiller->aniFrames, animator->animationID, &debris->animator, true, animator->frameID);
		debris->velocity.x      = RSDK.Rand(-0x20000, 0x20000);
		debris->velocity.y      = RSDK.Rand(-0x20000, -0x10000);
		debris->gravityStrength = 0x4800;
		debris->drawGroup       = Zone->objectDrawGroup[1];
		debris->updateRange.x   = 0x400000;
		debris->updateRange.y   = 0x400000;
	}
	BreakBadnik(player, e);
}