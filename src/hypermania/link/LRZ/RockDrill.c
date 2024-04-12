#include "RockDrill.h"

ObjectRockDrill* RockDrill;
void (*RockDrill_State_Drilling)();

bool32 RockDrill_CheckVulnerable(Entity* self) {
	return (!((EntityRockDrill*)self)->invincibilityTimer && ((EntityRockDrill*)self)->state == RockDrill_State_Drilling);
}

Hitbox* RockDrill_GetHitbox(Entity* self) { return &(RockDrill->hitboxBody); } // this is technically not accurate but it shows up for 5 seconds who cares

void RockDrill_OnHit(EntityPlayer* player, Entity* self) {
	RSDK.PlaySfx(RockDrill->sfxHit, false, 255);
	((EntityRockDrill*)self)->invincibilityTimer = 30;
}

void RockDrill_EnemyInfoHook() {
	Mod.Super(RockDrill->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(RockDrill->classID, RockDrill_CheckVulnerable, RockDrill_GetHitbox, RockDrill_OnHit, NULL, ATKFLAG_ISBOSS);
}