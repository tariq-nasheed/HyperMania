#ifndef OBJ_BALLHOG_H
#define OBJ_BALLHOG_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxBomb;
    uint16 aniFrames;
    uint16 sfxExplosion;
    uint16 sfxArrowHit;
    uint16 sfxDrop;
    uint16 sfxJump;
} ObjectBallHog;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 numJumps;
    uint8 bombTime;
    uint8 timer;
    uint8 jumpCount;
    Vector2 startPos;
    uint8 startDir;
    Animator animator;
} EntityBallHog;

extern ObjectBallHog *BallHog;

extern void (*BallHog_State_Bomb)();

void BallHog_EnemyInfoHook();

#define OBJ_BALLHOG_SETUP \
  IMPORT_PUBLIC_FUNC(BallHog_State_Bomb); \
  REGISTER_ENEMY(BallHog)

#endif //! OBJ_BALLHOG_H
