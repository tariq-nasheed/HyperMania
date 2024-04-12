#include "UberCaterkiller.h"

ObjectUberCaterkiller* UberCaterkiller;
void (*UberCaterkiller_State_HorizontalJump)();
void (*UberCaterkiller_State_FirstJump)();
void (*UberCaterkiller_State_RepeatedJumps)();
void (*UberCaterkiller_Hit)();
Hitbox hitboxSegment;

bool32 UberCaterkiller_CheckVulnerable(Entity* self) {
	const int32 scale = ((EntityUberCaterkiller*)self)->bodyScales[0];
	if (((EntityUberCaterkiller*)self)->invincibilityTimer || !(scale > 0x1C0 && scale < 0x240)) return false;
	return (
	    ((EntityUberCaterkiller*)self)->state == UberCaterkiller_State_HorizontalJump
	 || ((EntityUberCaterkiller*)self)->state == UberCaterkiller_State_FirstJump
	 || ((EntityUberCaterkiller*)self)->state == UberCaterkiller_State_RepeatedJumps
	);
}

Hitbox* UberCaterkiller_GetHitbox(Entity* self) {
	hitboxSegment.right  = (32 * ((EntityUberCaterkiller*)self)->bodyScales[0]) >> 9;
	hitboxSegment.bottom = hitboxSegment.right;
	hitboxSegment.left   = -hitboxSegment.right;
	hitboxSegment.top    = -hitboxSegment.right;
	return &(hitboxSegment);
}

void UberCaterkiller_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	UberCaterkiller_Hit();
	SceneInfo->entity = old_entity;
}

void UberCaterkiller_EnemyInfoHook(void) {
	Mod.Super(UberCaterkiller->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(UberCaterkiller->classID, UberCaterkiller_CheckVulnerable, UberCaterkiller_GetHitbox, UberCaterkiller_OnHit, NULL, ATKFLAG_ISBOSS);
}