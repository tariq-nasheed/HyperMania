#ifndef OBJ_BLASTER_H
#define OBJ_BLASTER_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxRange;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
} ObjectBlaster;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint16 unused1;
    uint16 timer;
    uint16 attackTimer;
    Vector2 startPos;
    uint8 startDir;
    Animator animator;
} EntityBlaster;

extern ObjectBlaster *Blaster;
void Blaster_EnemyInfoHook(void);
extern void (*Blaster_State_Move)(void);
extern void (*Blaster_State_HandleTurn)(void);
extern void (*Blaster_State_AttackPlayer)(void);
extern void (*Blaster_State_MagnetAttract)(void);
extern void (*Blaster_State_MagnetReleased)(void);
extern void (*Blaster_State_Fall)(void);

#endif //! OBJ_BLASTER_H
