#ifndef OBJ_RATTLEKILLER_H
#define OBJ_RATTLEKILLER_H

#include "GameAPI/Game.h"

#define RATTLEKILLER_SEGMENT_COUNT (10)

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxSegment;
    uint16 sfxRocketJet;
    uint16 aniFrames;
} ObjectRattlekiller;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);     // Unused
    StateMachine(stateDraw); // Unused
    int32 timer;
    int32 bodyStates[RATTLEKILLER_SEGMENT_COUNT];
    Vector2 bodyPositions[RATTLEKILLER_SEGMENT_COUNT];
    Vector2 bodyOriginPos[RATTLEKILLER_SEGMENT_COUNT];
    Vector2 bodyVelocities[RATTLEKILLER_SEGMENT_COUNT];
    int32 bodyAngles[RATTLEKILLER_SEGMENT_COUNT];
    int32 bodyDepth[RATTLEKILLER_SEGMENT_COUNT];
    int32 bodyDelays[RATTLEKILLER_SEGMENT_COUNT];
    int32 bodyIDs[RATTLEKILLER_SEGMENT_COUNT];
    Animator *bodyAnimators[RATTLEKILLER_SEGMENT_COUNT];
    Vector2 topBounds;
    Vector2 bottomBounds;
    Vector2 targetPos;
    int32 length;
    Animator headAnimator;
    Animator bodyAnimator;
    Animator tailAnimator;
} EntityRattlekiller;

extern ObjectRattlekiller *Rattlekiller;

void Rattlekiller_EnemyInfoHook(void);
void Rattlekiller_SpawnDebris(EntityPlayer* player, Entity* e);

#endif //! OBJ_RATTLEKILLER_H
