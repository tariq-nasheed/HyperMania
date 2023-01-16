#ifndef OBJ_DRAGONFLY_H
#define OBJ_DRAGONFLY_H

#include "GameAPI/Game.h"

#define DRAGONFLY_SPINE_COUNT (6)

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxSpine;
    uint16 aniFrames;
} ObjectDragonfly;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 dir;
    uint8 dist;
    uint8 speed;
    Vector2 positions[DRAGONFLY_SPINE_COUNT];
    uint8 directions[DRAGONFLY_SPINE_COUNT];
    Vector2 startPos;
    Animator animator;
    Animator wingAnimator;
    Animator bodyAnimator;
} EntityDragonfly;

extern ObjectDragonfly *Dragonfly;
void Dragonfly_EnemyInfoHook(void);
void Dragonfly_SpawnDebris(EntityPlayer* player, Entity* e);
extern void (*Dragonfly_State_Move)(void);

#endif //! OBJ_DRAGONFLY_H
