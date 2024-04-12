#pragma once

#define PAUSEMENU_BUTTON_COUNT (3)

struct ObjectPauseMenu {
    RSDK_OBJECT
    uint16 sfxBleep;
    uint16 sfxAccept;
    bool32 disableEvents;
    bool32 controllerDisconnect;
    bool32 forcedDisconnect;
    bool32 signOutDetected;
#if MANIA_USE_PLUS
    bool32 plusChanged;
#endif
    bool32 activeChannels[0x10];
#if MANIA_USE_PLUS
    uint16 tintLookupTable[0x10000];
#endif
};

struct EntityPauseMenu {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 timer;
    int32 tintAlpha;
    Vector2 headerPos;
    Vector2 yellowTrianglePos;
    Entity *manager;
    uint8 triggerPlayer;
    bool32 disableRestart;
    int32 buttonCount;
    uint8 buttonIDs[PAUSEMENU_BUTTON_COUNT];
    void (*buttonActions[PAUSEMENU_BUTTON_COUNT])(void);
    Entity *buttonPtrs[PAUSEMENU_BUTTON_COUNT];
    int32 paused;
    int32 fadeTimer;
    bool32 (*disconnectCheck)(void);
    int32 forcePaused;
    Animator animator;
    void (*fadeoutCB)(void);
    int32 unused1;
    int32 unused2; // these may possibly be leftover or editor things
};
