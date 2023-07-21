#ifndef OBJ_FLASHERMKII_H
#define OBJ_FLASHERMKII_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxFlop;
    uint16 sfxZap;
} ObjectFlasherMKII;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 orientation;
    int32 type;
    int32 timer;
    Vector2 startPos;
    Animator animator;
} EntityFlasherMKII;

extern ObjectFlasherMKII* FlasherMKII;

void FlasherMKII_EnemyInfoHook();

#define OBJ_FLASHERMKII_SETUP \
  REGISTER_ENEMY(FlasherMKII)

#endif //! OBJ_FLASHERMKII_H
