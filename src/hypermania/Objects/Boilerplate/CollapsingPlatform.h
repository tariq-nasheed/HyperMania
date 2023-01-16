#ifndef OBJ_COLLAPSINGPLATFORM_H
#define OBJ_COLLAPSINGPLATFORM_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    uint8 shift;
    Animator animator;
    uint16 aniFrames;
    uint16 sfxCrumble;
} ObjectCollapsingPlatform;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 size;
    bool32 respawn;
    uint16 targetLayer;
    uint8 type;
    int32 delay;
    bool32 eventOnly;
    bool32 mightyOnly;
    int32 unused1;
    int32 collapseDelay;
    uint16 storedTiles[256];
    Hitbox hitboxTrigger;
    Vector2 stoodPos;
} EntityCollapsingPlatform;

extern ObjectCollapsingPlatform *CollapsingPlatform;

#endif //! OBJ_COLLAPSINGPLATFORM_H
