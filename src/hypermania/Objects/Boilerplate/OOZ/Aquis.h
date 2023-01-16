#ifndef OBJ_AQUIS_H
#define OBJ_AQUIS_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxRange;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
    uint16 sfxShot;
} ObjectAquis;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    uint8 playerInRange;
    int32 remainingTurns;
    Vector2 startPos;
    uint8 startDir;
    Animator mainAnimator;
    Animator wingAnimator;
} EntityAquis;

extern ObjectAquis *Aquis;

void Aquis_EnemyInfoHook(void);
extern void (*Aquis_State_Idle)(void);
extern void (*Aquis_State_Moving)(void);
extern void (*Aquis_State_Shoot)(void);
extern void (*Aquis_State_Turning)(void);
extern void (*Aquis_State_Flee)(void);

#endif //! OBJ_AQUIS_H
