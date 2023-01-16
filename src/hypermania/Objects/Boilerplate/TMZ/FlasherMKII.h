#ifndef OBJ_FLASHERMKII_H
#define OBJ_FLASHERMKII_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxFlop;
    uint16 sfxZap;
} ObjectFlasherMKII;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 orientation;
    int32 type;
    int32 timer;
    Vector2 startPos;
    Animator animator;
} EntityFlasherMKII;

extern ObjectFlasherMKII *FlasherMKII;

void FlasherMKII_EnemyInfoHook(void);
void FlasherMKII_StopSound(EntityPlayer* player, Entity* e);
extern void (*FlasherMKII_State_Idle)(void);
extern void (*FlasherMKII_State_Moving)(void);
extern void (*FlasherMKII_State_WeakFlash)(void);
extern void (*FlasherMKII_State_StrongFlash)(void);
extern void (*FlasherMKII_State_FinishedFlashing)(void);

#endif //! OBJ_FLASHERMKII_H
