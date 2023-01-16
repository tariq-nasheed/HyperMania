#ifndef OBJ_BUZZBOMBER_H
#define OBJ_BUZZBOMBER_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
} ObjectBuzzBomber;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 shotRange;
    int32 timer;
    uint8 detectedPlayer;
    Vector2 startPos;
    uint8 startDir;
    Entity *projectile;
    Animator animator;
    Animator wingAnimator;
    Animator thrustAnimator;
    Hitbox hitboxRange;
} EntityBuzzBomber;

extern ObjectBuzzBomber *BuzzBomber;
void BuzzBomber_EnemyInfoHook(void);
void BuzzBomber_DestroyProjectile(EntityPlayer* player, Entity* e);
extern void (*BuzzBomber_State_Flying)(void);
extern void (*BuzzBomber_State_Idle)(void);
extern void (*BuzzBomber_State_DetectedPlayer)(void);

#endif //! OBJ_BUZZBOMBER_H
