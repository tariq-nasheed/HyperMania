#pragma once

// Object Struct
extern ObjectCamera *Camera;

// Imported Functions
extern void (*Camera_State_FollowXY)();
extern void (*Camera_State_FollowY)();
extern void (*Camera_ShakeScreen)(int32 screen, int32 shakeX, int32 shakeY);
extern void (*Camera_SetupLerp)(int32 type, int32 screen, int32 x, int32 y, int32 speed);