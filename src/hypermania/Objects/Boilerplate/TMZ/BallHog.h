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

void BallHog_EnemyInfoHook(void);
extern void (*BallHog_State_Idle)(void);
extern void (*BallHog_State_Jump)(void);
extern void (*BallHog_State_Land)(void);
extern void (*BallHog_State_DropBomb)(void);

#endif //! OBJ_BALLHOG_H
