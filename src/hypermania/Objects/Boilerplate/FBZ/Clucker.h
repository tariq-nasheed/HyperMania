#ifndef OBJ_CLUCKER_H
#define OBJ_CLUCKER_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxRange;
    Hitbox hitboxSolid;
    Hitbox hitboxEgg;
    uint16 aniFrames;
    uint16 sfxShot;
} ObjectClucker;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 yOffset;
    int32 xOffset;
    uint8 timer;
    uint16 delay;
    bool32 hasParent;
    Animator animator;
} EntityClucker;

extern ObjectClucker *Clucker;
void Clucker_EnemyInfoHook(void);
void Clucker_DestroyPilot(EntityPlayer* player, Entity* e);
extern void (*Clucker_State_Appear)(void);
extern void (*Clucker_State_ShootDelay)(void);
extern void (*Clucker_State_Shoot)(void);
extern void (*Clucker_State_Turn)(void);
extern void (*Clucker_State_Destroyed)(void);

#endif //! OBJ_CLUCKER_H
