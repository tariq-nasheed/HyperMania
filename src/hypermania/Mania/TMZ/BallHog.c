#include "BallHog.h"

ObjectBallHog *BallHog;
void (*BallHog_State_Bomb)();

bool32 BallHog_CheckVulnerable(Entity* self) {
	return (((EntityBallHog*)self)->state != BallHog_State_Bomb);
}

Hitbox* BallHog_GetHitbox(Entity* self) { return &(BallHog->hitboxBadnik); }

void BallHog_EnemyInfoHook() {
	Mod.Super(BallHog->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(BallHog->classID, BallHog_CheckVulnerable, BallHog_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}