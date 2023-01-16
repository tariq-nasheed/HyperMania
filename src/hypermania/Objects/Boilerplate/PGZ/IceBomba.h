#ifndef OBJ_ICEBOMBA_H
#define OBJ_ICEBOMBA_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxBomb;
    Hitbox hitboxRange;
    uint16 aniFrames;
    uint16 sfxExplosion;
    uint16 sfxFreeze;
} ObjectIceBomba;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 dir;
    uint16 dist;
    uint16 dip;
    uint8 startDir;
    Vector2 startPos;
    uint32 startDist;
    Animator bodyAnimator;
    Animator wingAnimator;
    Animator bombAnimator;
} EntityIceBomba;

extern ObjectIceBomba *IceBomba;
void IceBomba_EnemyInfoHook(void);
void IceBomba_DropBomb(EntityPlayer* player, Entity* e);
extern void (*IceBomba_State_Flying)(void);
extern void (*IceBomba_State_Turning)(void);
extern void (*IceBomba_State_FlyAway)(void);

#endif //! OBJ_ICEBOMBA_H
