#ifndef OBJ_BLASTOID_H
#define OBJ_BLASTOID_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBody;
    Hitbox hitboxProjectile;
    uint16 aniFrames;
    uint16 sfxShot;
} ObjectBlastoid;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 timer;
    Animator animator;
} EntityBlastoid;

extern ObjectBlastoid *Blastoid;

void Blastoid_EnemyInfoHook(void);
void Blastoid_Destroy(EntityPlayer* player, Entity* e);
extern void (*Blastoid_State_Body)(void);

#endif //! OBJ_BLASTOID_H
