#ifndef OBJ_SPINY_H
#define OBJ_SPINY_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxSpiny;
    Hitbox hitboxRange;
    Hitbox hitboxShot;
    uint16 aniFrames;
    uint16 sfxShot;
} ObjectSpiny;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Animator animator;
    int32 unused;
    uint8 type;
    Vector2 startPos;
    uint8 startDir;
    int32 shotVelocity;
    int32 dirChangeTimer;
    int32 moveTimer;
} EntitySpiny;

extern ObjectSpiny *Spiny;
void Spiny_EnemyInfoHook(void);
extern void (*Spiny_State_Floor)(void);
extern void (*Spiny_State_Shoot_Floor)(void);
extern void (*Spiny_State_Wall)(void);
extern void (*Spiny_State_Shoot_Wall)(void);

#endif //! OBJ_SPINY_H
