#ifndef OBJ_BUBBLER_H
#define OBJ_BUBBLER_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxRange;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
} ObjectBubbler;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int16 timer;
    uint16 spawnTimer;
    Vector2 startPos;
    uint8 startDir;
    Animator bodyHitbox;
    Animator flameAnimator;
} EntityBubbler;

extern ObjectBubbler *Bubbler;
void Bubbler_EnemyInfoHook(void);
extern void (*Bubbler_State_MotherPatrol)(void);
extern void (*Bubbler_State_FoundPlayer)(void);
extern void (*Bubbler_State_AttackPlayer)(void);
extern void (*Bubbler_StateProjectile_Seed)(void);
extern void (*Bubbler_StateProjectile_Bubbler)(void);

#endif //! OBJ_BUBBLER_H
