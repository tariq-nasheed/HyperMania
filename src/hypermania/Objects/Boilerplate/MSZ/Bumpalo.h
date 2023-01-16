#ifndef OBJ_BUMPALO_H
#define OBJ_BUMPALO_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxBumper;
    Hitbox hitboxRange;
    Hitbox hitboxCharge;
    Hitbox hitboxUnused;
    uint16 aniFrames;
    uint16 sfxBumper;
    uint16 sfxHuff;
    uint16 sfxClack;
    uint16 sfxImpact;
} ObjectBumpalo;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    uint8 startDir;
    int32 timer;
    bool32 ignoreCliffs;
    bool32 wallCollided;
    Animator badnikAnimator;
    Animator huffAnimator;
    Animator dustAnimator;
} EntityBumpalo;

extern ObjectBumpalo *Bumpalo;

void Bumpalo_EnemyInfoHook(void);
extern void (*Bumpalo_State_Moving)(void);
extern void (*Bumpalo_State_Idle)(void);
extern void (*Bumpalo_State_Charging)(void);
extern void (*Bumpalo_State_Turning)(void);
extern void (*Bumpalo_State_Bumped)(void);
extern void (*Bumpalo_State_Falling)(void);

#endif //! OBJ_BUMPALO_H
