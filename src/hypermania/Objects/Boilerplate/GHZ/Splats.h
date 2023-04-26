#ifndef OBJ_SPLATS_H
#define OBJ_SPLATS_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    StateMachine(initialState);
    Hitbox hitboxBadnikGHZ;
    Hitbox hitboxJar;
    Hitbox hitboxBadnikPGZ;
    uint16 aniFrames;
    uint16 sfxSplatsSpawn;
    uint16 sfxSplatsLand;
} ObjectSplats;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 bounceCount;
    uint8 activeCount;
    uint8 numActive;
    uint16 minDelay;
    int32 delay;
    bool32 isOnScreen;
    Entity *parent; // all pointer types are the same size who gives a shit
    Vector2 startPos;
    int32 startDir;
    Animator mainAnimator;
    Animator splashAnimator;
} EntitySplats;

extern ObjectSplats *Splats;
void Splats_EnemyInfoHook(void);
extern void (*Splats_State_BounceAround)(void);
extern void (*Splats_State_JumpOutOfJar)(void);
extern void (*Splats_State_HandleBouncing)(void);
extern void (*Splats_State_HandleLanding)(void);
extern void (*Splats_State_NoMoreJumps)(void);

#endif //! OBJ_SPLATS_H
