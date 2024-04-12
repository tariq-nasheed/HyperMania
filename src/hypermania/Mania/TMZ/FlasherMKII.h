#pragma once

struct ObjectFlasherMKII {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxFlop;
    uint16 sfxZap;
};

struct EntityFlasherMKII {
    RSDK_ENTITY
    StateMachine(state);
    uint8 orientation;
    int32 type;
    int32 timer;
    Vector2 startPos;
    Animator animator;
};
