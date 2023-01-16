#ifndef OBJ_POHBEE_H
#define OBJ_POHBEE_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    uint16 aniFrames;
} ObjectPohBee;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    uint8 startDir;
    int32 chainPos[2];
    int32 chainAngle[2];
    int32 unused;
    bool32 isTurning;
    Animator bodyAnimator;
    Animator wingsAnimator;
    Animator chainAnimator;
    Animator spikeAnimator;
    Hitbox hitboxes[2];
    uint8 spikeCount;
    Vector2 amplitude;
    ManiaPlaneFilterTypes planeFilter;
} EntityPohBee;

extern ObjectPohBee *PohBee;

void PohBee_EnemyInfoHook(void);
void PohBee_Destroy(EntityPlayer* player, Entity* e);

#endif //! OBJ_POHBEE_H
