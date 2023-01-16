#ifndef OBJ_CATERKILLERJR_H
#define OBJ_CATERKILLERJR_H

#include "GameAPI/Game.h"

#define CATERKILLERJR_SEGMENT_COUNT (7)

typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    uint16 aniFrames;
} ObjectCaterkillerJr;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    Vector2 startPos;
    Vector2 bodyPosition[8];
    Vector2 bodyVelocity[8];
    int32 bodyDirection[8];
    int32 bodyTimer[8];
    int32 boundsL;
    int32 boundsR;
    Animator bodyAnimators[CATERKILLERJR_SEGMENT_COUNT];
    Animator smokePuffAnimators[3];
} EntityCaterkillerJr;

extern ObjectCaterkillerJr *CaterkillerJr;
void CaterkillerJr_EnemyInfoHook(void);
void CaterkillerJr_SpawnDebris(EntityPlayer* player, Entity* e);
extern void (*CaterkillerJr_State_Move)(void);

#endif //! OBJ_CATERKILLERJR_H
