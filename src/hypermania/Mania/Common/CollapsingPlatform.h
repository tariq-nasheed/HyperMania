#pragma once

struct ObjectCollapsingPlatform {
    RSDK_OBJECT
    uint8 shift;
    Animator animator;
    uint16 aniFrames;
    uint16 sfxCrumble;
};

struct EntityCollapsingPlatform {
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
};
