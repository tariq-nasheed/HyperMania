#ifndef OBJ_BATBRAIN_H
#define OBJ_BATBRAIN_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    uint16 aniFrames;
    uint16 sfxFlap;
} ObjectBatbrain;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 targetY;
    EntityPlayer *target;
    Vector2 startPos;
    Animator animator;
} EntityBatbrain;

extern ObjectBatbrain *Batbrain;
void Batbrain_EnemyInfoHook(void);
extern void (*Batbrain_State_CheckPlayerInRange)(void);
extern void (*Batbrain_State_DropToPlayer)(void);
extern void (*Batbrain_State_Fly)(void);
extern void (*Batbrain_State_FlyToCeiling)(void);

#endif //! OBJ_BATBRAIN_H
