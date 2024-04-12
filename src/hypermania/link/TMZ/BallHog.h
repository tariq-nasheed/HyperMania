#pragma once

extern ObjectBallHog *BallHog;

extern void (*BallHog_State_Bomb)();

void BallHog_EnemyInfoHook();

#define OBJ_BALLHOG_SETUP \
  IMPORT_PUBLIC_FUNC(BallHog_State_Bomb); \
  REGISTER_ENEMY(BallHog)