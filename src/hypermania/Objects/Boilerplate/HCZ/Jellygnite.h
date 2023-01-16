#ifndef OBJ_JELLYGNITE_H
#define OBJ_JELLYGNITE_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    Hitbox hitboxUnused;
    uint16 aniFrames;
    uint16 sfxGrab;
    uint16 sfxElectrify;
} ObjectJellygnite;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 startPos;
    uint8 startDir;
    uint8 timer;
    uint8 grabDelay;
    int32 frontTentacleAngle;
    int32 oscillateAngle;
    EntityPlayer *grabbedPlayer;
    uint8 shakeTimer;
    uint8 shakeCount;
    uint8 lastShakeFlags;
    uint8 prevAnimationID;
    Animator bodyAnimator;
    Animator frontTentacleAnimator;
    Animator backTentacleAnimator;
} EntityJellygnite;

extern ObjectJellygnite *Jellygnite;

void Jellygnite_EnemyInfoHook(void);
void Jellygnite_Destroy(EntityPlayer* player, Entity* e);
extern void (*Jellygnite_State_Swimming)(void);
extern void (*Jellygnite_State_GrabbedPlayer)(void);

#endif //! OBJ_JELLYGNITE_H
