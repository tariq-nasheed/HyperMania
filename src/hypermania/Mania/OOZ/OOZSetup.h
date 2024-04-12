#pragma once

struct ObjectOOZSetup {
    RSDK_OBJECT
    int32 palTimer;
    uint16 aniTiles;
    TileLayer *background1;
    TABLE(int32 deformData[64], { 1, 2, 1, 3, 1, 2, 2, 1, 2, 3, 1, 2, 1, 2, 0, 0, 2, 0, 3, 2, 2, 3, 2, 2, 1, 3, 0, 0, 1, 0, 1, 3,
                                  1, 2, 1, 3, 1, 2, 2, 1, 2, 3, 1, 2, 1, 2, 0, 0, 2, 0, 3, 2, 2, 3, 2, 2, 1, 3, 0, 0, 1, 0, 1, 3 });
    int32 oilAniTimer;
    int32 glowLightAniFrame;
    STATIC(int32 glowLightAniTimer, 60);
    TABLE(int32 glowLightAniDurations[9], { 60, 60, 3, 3, 3, 3, 3, 3, 4 });
    int32 swimmingPlayerCount;
    int32 smogTimer;
    int32 useSmogEffect;
    uint8 flameTimers[0x20000];
    uint8 *flameTimerPtrs[400];
    Vector2 flamePositions[400];
    uint16 flameCount;
    uint8 activePlayers;
#if MANIA_USE_PLUS
    Animator flameAnimator;
    Animator animator;
    uint16 solFrames;
    uint16 splashFrames;
#else
    Animator flameAnimator;
    uint16 solFrames;
#endif
    bool32 hasAchievement;
    Entity *cutscenePtr;
};

struct EntityOOZSetup {
    RSDK_ENTITY
    uint8 type;
};
