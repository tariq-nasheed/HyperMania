#ifndef OBJ_ERZSTART_H
#define OBJ_ERZSTART_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    int32 timer;
    int32 unused1;
    int32 superDashCooldown;
    int32 unused2;
    uint16 sfxClack;
    uint16 sfxFlyIn;
    uint16 sfxHullClose;
    uint16 sfxRumble;
    void *fxRuby;
    void *ruby;
    void *emeralds[7];
    void *king;
    void *eggman;
} ObjectERZStart;

typedef struct {
    MANIA_CUTSCENE_BASE
    int32 timer;
} EntityERZStart;

extern ObjectERZStart *ERZStart;

#endif //! OBJ_ERZSTART_H
