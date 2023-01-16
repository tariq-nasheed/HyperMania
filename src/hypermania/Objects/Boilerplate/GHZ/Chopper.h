#ifndef OBJ_CHOPPER_H
#define OBJ_CHOPPER_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxJump;
    Hitbox hitboxSwim;
    Hitbox hitboxRange;
    Hitbox hitboxWater;
    uint16 aniFrames;
} ObjectChopper;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    uint16 timer;
    bool32 charge;
    Vector2 startPos;
    uint8 startDir;
    Animator animator;
} EntityChopper;

extern ObjectChopper *Chopper;
void Chopper_EnemyInfoHook(void);
extern void (*Chopper_State_Jump)(void);
extern void (*Chopper_State_Swim)(void);
extern void (*Chopper_State_ChargeDelay)(void);

#endif //! OBJ_CHOPPER_H
