#ifndef OBJ_OCTUS_H
#define OBJ_OCTUS_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxProjectile;
    Hitbox hitboxRange;
    uint16 aniFrames;
    uint16 sfxShot;
} ObjectOctus;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    uint8 unused1;
    Vector2 startPos;
    uint8 startDir;
    int32 unused2;
    Animator animator;
} EntityOctus;

extern ObjectOctus *Octus;

void Octus_EnemyInfoHook(void);
extern void (*Octus_State_CheckPlayerInRange)(void);
extern void (*Octus_State_JumpDelay)(void);
extern void (*Octus_State_Jump)(void);
extern void (*Octus_State_Shoot)(void);
extern void (*Octus_State_Fall)(void);

#endif //! OBJ_OCTUS_H
