#ifndef OBJ_HATTERKILLER_H
#define OBJ_HATTERKILLER_H

#include "GameAPI/Game.h"

#define HATTERKILLER_SEGMENT_COUNT (10)

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxSegment;
    uint16 sfxRocketJet;
    uint16 sfxTransform2;
    uint16 sfxPowerup;
    uint16 aniFrames;
} ObjectHatterkiller;

typedef struct {
    RSDK_ENTITY
    int32 timer;
    Vector2 bodyPositions[HATTERKILLER_SEGMENT_COUNT];
    Vector2 bodyVelocities[HATTERKILLER_SEGMENT_COUNT];
    int32 bodyDelays[HATTERKILLER_SEGMENT_COUNT];
    Animator *bodyAnimators[HATTERKILLER_SEGMENT_COUNT];
    Animator headAnimator;
    Animator bodyAnimator;
    Animator tailAnimator;
} EntityHatterkiller;

extern ObjectHatterkiller *Hatterkiller;

void Hatterkiller_EnemyInfoHook(void);
void Hatterkiller_SpawnDebris(EntityPlayer* player, Entity* e);

#endif //! OBJ_HATTERKILLER_H
