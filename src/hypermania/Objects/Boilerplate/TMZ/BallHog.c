#include "BallHog.h"

ObjectBallHog *BallHog;
void (*BallHog_State_Idle)(void);
void (*BallHog_State_Jump)(void);
void (*BallHog_State_Land)(void);
void (*BallHog_State_DropBomb)(void);

void BallHog_EnemyInfoHook(void) {
	Mod.Super(BallHog->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = BallHog->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = BallHog_State_Idle;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &BallHog->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = BallHog_State_Jump;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &BallHog->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = BallHog_State_Land;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &BallHog->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = BallHog_State_DropBomb;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &BallHog->hitboxBadnik;
	++EnemyInfoSlot;
}
