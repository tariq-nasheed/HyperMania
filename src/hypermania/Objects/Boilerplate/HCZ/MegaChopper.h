#ifndef OBJ_MEGACHOPPER_H
#define OBJ_MEGACHOPPER_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxChop;
    uint16 aniFrames;
} ObjectMegaChopper;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    EntityPlayer *grabbedPlayer;
    Vector2 playerPos;
    uint8 playerDir;
    uint16 shakeTimer;
    uint16 shakeCount;
    uint16 lastShakeFlags;
    uint8 nibbleTimer;
    Animator animator;
} EntityMegaChopper;

extern ObjectMegaChopper *MegaChopper;

void MegaChopper_EnemyInfoHook(void);
extern void (*MegaChopper_State_InWater)(void);
extern void (*MegaChopper_State_OutOfWater)(void);

#endif //! OBJ_MEGACHOPPER_H
