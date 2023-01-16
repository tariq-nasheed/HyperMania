#ifndef OBJ_JAWZ_H
#define OBJ_JAWZ_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    uint16 aniFrames;
} ObjectJawz;

typedef struct {
    RSDK_ENTITY
    uint8 triggerDir;
    StateMachine(state);
    Vector2 startPos;
    Animator animator;
} EntityJawz;

extern ObjectJawz *Jawz;

void Jawz_EnemyInfoHook(void);
extern void (*Jawz_State_Triggered)(void);

#endif //! OBJ_JAWZ_H
