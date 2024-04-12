#pragma once

#define CATERKILLERJR_SEGMENT_COUNT (7)

struct ObjectCaterkillerJr {
    RSDK_OBJECT
    Hitbox hitbox;
    uint16 aniFrames;
};

struct EntityCaterkillerJr {
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
};
