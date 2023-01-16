#ifndef OBJ_NEWTRON_H
#define OBJ_NEWTRON_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxShoot;
    Hitbox hitboxFly; // not sure why isn't this used in this object... GHZ/CheckerBall uses it though
    Hitbox hitboxProjectile;
    Hitbox hitboxRange;
    uint16 aniFrames;
} ObjectNewtron;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    int32 timer;
    Vector2 startPos;
    Animator animator;
    Animator flameAnimator;
} EntityNewtron;

extern ObjectNewtron *Newtron;
void Newtron_EnemyInfoHook(void);
extern void (*Newtron_State_StartFly)(void);
extern void (*Newtron_State_Fly)(void);
extern void (*Newtron_State_Shoot)(void);

#endif //! OBJ_NEWTRON_H
