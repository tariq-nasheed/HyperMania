#ifndef OBJ_CRABMEAT_H
#define OBJ_CRABMEAT_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
} ObjectCrabmeat;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    uint8 shootState;
    Vector2 startPos;
    int32 startDir;
    Animator animator;
} EntityCrabmeat;

extern ObjectCrabmeat *Crabmeat;
void Crabmeat_EnemyInfoHook(void);
extern void (*Crabmeat_State_Moving)(void);
extern void (*Crabmeat_State_Shoot)(void);

#endif //! OBJ_CRABMEAT_H
