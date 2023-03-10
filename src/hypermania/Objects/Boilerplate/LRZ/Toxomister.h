#ifndef OBJ_TOXOMISTER_H
#define OBJ_TOXOMISTER_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxCloud;
    uint16 aniFrames;
} ObjectToxomister;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    uint8 startDir;
    Entity *parent;
    EntityPlayer *grabbedPlayer;
    int32 timer;
    uint16 shakeTimer;
    uint16 shakeCount;
    uint16 prevShakeFlags;
    Animator animator;
} EntityToxomister;

extern ObjectToxomister *Toxomister;

void Toxomister_EnemyInfoHook(void);
void Toxomister_DestroyCloud(EntityPlayer* player, Entity* e);
extern void (*Toxomister_State_CreateClouds)(void);

#endif //! OBJ_TOXOMISTER_H
