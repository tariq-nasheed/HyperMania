#ifndef OBJ_TURBOSPIKER_H
#define OBJ_TURBOSPIKER_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxSpike;
    Hitbox hitboxRange;
    uint16 aniFrames;
    uint16 sfxLaunch;
    uint16 sfxSplash;
} ObjectTurboSpiker;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint32 type;
    int32 timer;
    int32 unused;
    Vector2 startPos;
    uint8 startDir;
    Entity *spike;
    Animator shellAnimator;
    Animator animator;
    bool32 playedLaunchSfx;
} EntityTurboSpiker;

extern ObjectTurboSpiker *TurboSpiker;

void TurboSpiker_EnemyInfoHook(void);
void TurboSpiker_DestroySpike(EntityPlayer* player, Entity* e);
extern void (*TurboSpiker_State_Idle)(void);
extern void (*TurboSpiker_State_Hidden)(void);
extern void (*TurboSpiker_State_Moving)(void);
extern void (*TurboSpiker_State_Turning)(void);
extern void (*TurboSpiker_State_FinishTurning)(void);
extern void (*TurboSpiker_State_Falling)(void);
extern void (*TurboSpiker_State_FireShell)(void);

#endif //! OBJ_TURBOSPIKER_H
