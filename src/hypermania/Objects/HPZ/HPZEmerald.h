#ifndef OBJ_HPZEMERALD_H
#define OBJ_HPZEMERALD_H

#include "GameAPI/Game.h"

typedef enum {
    HPZEMERALD_MASTER,
    HPZEMERALD_EMERALD_LOW,
    HPZEMERALD_EMERALD_HIGH,
} HPZEmeraldTypes;

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectHPZEmerald;

typedef struct {
    RSDK_ENTITY
    StateMachine(state); // unused... until NOW!!!!
    uint8 type;
    bool32 solid;
    Vector2 startPos;
    Hitbox *hitbox;
    Animator emeraldAnimator;
    Animator overlayAnimator;
} EntityHPZEmerald;

extern ObjectHPZEmerald *HPZEmerald;

// Overload Functions
void HPZEmerald_Update_Hook(void);
void HPZEmerald_Draw_Hook(void);
void HPZEmerald_Create_Hook(void* data);
void HPZEmerald_StageLoad_Hook(void);

#endif //! OBJ_HPZEMERALD_H
