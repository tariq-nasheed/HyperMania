#ifndef OBJ_HOTARUMKII_H
#define OBJ_HOTARUMKII_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxLaser;
    uint16 aniFrames;
    uint16 sfxAppear;
    uint16 sfxLaser;
    uint16 sfxFly;
    uint16 sfxCharge;
} ObjectHotaruMKII;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    uint8 startDir;
    int32 timer;
    Vector2 moveAcceleration;
    uint8 unused1;
    uint8 unused2;
    uint8 childCount;
    Vector2 curOffset;
    uint8 origin;
    Vector2 offset1;
    Vector2 offset2;
    Vector2 offset3;
    int32 offsetID;
    EntityPlayer *playerPtr;
    int32 type;
    Vector2 triggerSize;
    Hitbox hitboxTrigger;
    Animator mainAnimator;
    Animator flashAnimator;
    Animator unusedAnimator;
} EntityHotaruMKII;

extern ObjectHotaruMKII *HotaruMKII;

void HotaruMKII_EnemyInfoHook(void);
extern void (*HotaruMKII_State_Charging)(void);
extern void (*HotaruMKII_State_LaserAttack)(void);

#endif //! OBJ_HOTARUMKII_H
