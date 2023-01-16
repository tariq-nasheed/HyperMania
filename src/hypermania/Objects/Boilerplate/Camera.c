#include "Camera.h"

ObjectCamera *Camera;
void (*Camera_State_FollowY)(void);
void (*Camera_ShakeScreen)(int32 screen, int32 shakeX, int32 shakeY);
