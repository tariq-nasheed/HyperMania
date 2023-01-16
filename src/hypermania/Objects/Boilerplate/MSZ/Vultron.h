#ifndef OBJ_VULTRON_H
#define OBJ_VULTRON_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxRange;
    uint16 aniFrames;
    uint16 sfxVultron;
} ObjectVultron;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    Vector2 startPos;
    uint8 startDir;
    uint16 dist;
    uint16 distRemain;
    int32 storeY;
    Hitbox hitboxBadnik;
    Animator bodyAnimator;
    Animator flameAnimator;
} EntityVultron;

extern ObjectVultron *Vultron;

void Vultron_EnemyInfoHook(void);
extern void (*Vultron_State_CheckPlayerInRange)(void);
extern void (*Vultron_State_Hop)(void);
extern void (*Vultron_State_Dive)(void);
extern void (*Vultron_State_Flying)(void);
extern void (*Vultron_State_Rise)(void);
extern void (*Vultron_State_PrepareDive)(void);
extern void (*Vultron_State_Targeting)(void);

#endif //! OBJ_VULTRON_H
