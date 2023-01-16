#ifndef OBJ_DEBRIS_H
#define OBJ_DEBRIS_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
} ObjectDebris;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 gravityStrength;
    int32 rotSpeed;
    Vector2 scaleSpeed;
    int32 delay;
    Animator animator;
} EntityDebris;

extern ObjectDebris *Debris;

// Imported Functions
extern void (*Debris_State_Move)(void);
extern void (*Debris_State_FallAndFlicker)(void);

#endif //! OBJ_DEBRIS_H
