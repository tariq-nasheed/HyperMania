#pragma once

typedef enum {
    CAMERA_LERP_NORMAL,
    CAMERA_LERP_SIN1024,
    CAMERA_LERP_SIN1024_2,
    CAMERA_LERP_SIN512,
} CameraLerpType;

// Object Class
struct ObjectCamera {
    RSDK_OBJECT
    Vector2 centerBounds;
};

// Entity Class
struct EntityCamera {
    RSDK_ENTITY
    StateMachine(state);
    Entity *target;
    int32 screenID;
    Vector2 center;
    Vector2 targetMoveVel;
    Vector2 lastPos;
    Vector2 shakePos;
    Vector2 lookPos;
    Vector2 offset;
    bool32 disableYOffset;
    int32 centerY;
    int32 adjustY;
    int32 lerpPercent;
    int32 lerpSpeed;
    int32 lerpType;
    Vector2 endLerpPos;
    Vector2 startLerpPos;
    Vector2 boundsOffset;
    int32 boundsL;
    int32 boundsR;
    int32 boundsT;
    int32 boundsB;
};
