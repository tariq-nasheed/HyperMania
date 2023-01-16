#ifndef OBJ_CAMERA_H
#define OBJ_CAMERA_H

#include "GameAPI/Game.h"

typedef enum {
    CAMERA_LERP_NORMAL,
    CAMERA_LERP_SIN1024,
    CAMERA_LERP_SIN1024_2,
    CAMERA_LERP_SIN512,
} CameraLerpType;

// Object Class
typedef struct {
    RSDK_OBJECT
    Vector2 centerBounds;
} ObjectCamera;

// Entity Class
typedef struct {
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
} EntityCamera;

// Object Struct
extern ObjectCamera *Camera;

// Imported Functions
extern void (*Camera_State_FollowY)(void);
extern void (*Camera_ShakeScreen)(int32 screen, int32 shakeX, int32 shakeY);

#endif //! OBJ_CAMERA_H
