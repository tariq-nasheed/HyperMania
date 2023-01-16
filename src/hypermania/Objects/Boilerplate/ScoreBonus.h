#ifndef OBJ_SCOREBONUS_H
#define OBJ_SCOREBONUS_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectScoreBonus;

typedef struct {
    RSDK_ENTITY
    int32 timer;
    Animator animator;
} EntityScoreBonus;

extern ObjectScoreBonus *ScoreBonus;

#endif //! OBJ_SCOREBONUS_H
