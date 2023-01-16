#ifndef OBJ_DANGO_H
#define OBJ_DANGO_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxCurlRange;
    uint16 aniFrames;
    uint16 sfxBumper;
} ObjectDango;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 rollDelay;
    bool32 preventStateChange;
    Vector2 startPos;
    uint8 startDir;
    Animator animator;
} EntityDango;

extern ObjectDango *Dango;

void Dango_EnemyInfoHook(void);
extern void (*Dango_State_Walking)(void);
extern void (*Dango_State_Turning)(void);
extern void (*Dango_State_Falling_Uncurled)(void);
extern void (*Dango_State_Curling)(void);
extern void (*Dango_State_Rolling)(void);
extern void (*Dango_State_Falling_Curled)(void);
extern void (*Dango_State_Uncurling)(void);

#endif //! OBJ_DANGO_H
