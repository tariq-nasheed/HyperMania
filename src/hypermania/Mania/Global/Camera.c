#include "Camera.h"

ObjectCamera *Camera;
void (*Camera_State_FollowXY)();
void (*Camera_State_FollowY)();
void (*Camera_ShakeScreen)(int32 screen, int32 shakeX, int32 shakeY);
void (*Camera_SetupLerp)(int32 type, int32 screen, int32 x, int32 y, int32 speed);