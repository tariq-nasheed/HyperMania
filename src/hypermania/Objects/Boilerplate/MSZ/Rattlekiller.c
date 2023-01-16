#include "Rattlekiller.h"

ObjectRattlekiller *Rattlekiller;

void Rattlekiller_EnemyInfoHook(void) {
	Mod.Super(Rattlekiller->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Rattlekiller->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Rattlekiller->hitboxSegment;
	EnemyDefs[EnemyInfoSlot].destroy_func = Rattlekiller_SpawnDebris;
	++EnemyInfoSlot;
}

void Rattlekiller_SpawnDebris(EntityPlayer* player, Entity* e) {
	EntityRattlekiller* self = (EntityRattlekiller*)e;
	for (int32 i = 1; i < RATTLEKILLER_SEGMENT_COUNT; ++i) {
		EntityDebris *debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, self->bodyPositions[i].x, self->bodyPositions[i].y);

		RSDK.SetSpriteAnimation(Rattlekiller->aniFrames, self->bodyAnimators[i]->animationID, &debris->animator, true,
		                        self->bodyAnimators[i]->frameID);
		debris->velocity.x      = RSDK.Rand(-0x20000, 0x20000);
		debris->velocity.y      = RSDK.Rand(-0x20000, -0x10000);
		debris->gravityStrength = 0x4800;
		debris->drawGroup       = Zone->objectDrawGroup[1];
		debris->updateRange.x   = 0x400000;
		debris->updateRange.y   = 0x400000;
	}
	BreakBadnik(player, e);
}