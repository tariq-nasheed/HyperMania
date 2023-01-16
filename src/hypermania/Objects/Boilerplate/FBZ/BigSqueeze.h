#ifndef OBJ_BIGSQUEEZE_H
#define OBJ_BIGSQUEEZE_H

#include "GameAPI/Game.h"

typedef enum {
    BIGSQUEEZE_MANAGER,
    BIGSQUEEZE_BOSS,
    BIGSQUEEZE_CRUSHER_L,
    BIGSQUEEZE_CRUSHER_R,
} BigSqueezeTypes;

typedef struct {
    RSDK_OBJECT
    TABLE(int32 prongDebrisInfo[10], { 3, 12, -0x20000, -0x10000, 13, 0, -0x10000, 14, 0x20000, -0x10000 });
    TABLE(int32 domeDebrisInfo[13], { 4, 8, -0x20000, -0x10000, 9, -0x10000, -0x10000, 10, 0x10000, -0x10000, 11, 0x20000, -0x10000 });
    TABLE(int32 baseDebrisInfo[25], { 8,       0, -0x20000, -0x10000, 1, -0x10000, -0x10000, 2, 0x10000, -0x10000, 3, 0x20000, -0x10000, 4, -0x20000,
                                      -0x8000, 5, -0x10000, -0x8000,  6, 0x10000,  -0x8000,  7, 0x20000, -0x8000 });
    int32 crusherX[4];
    bool32 isCrushing;
    int32 crushTimer;
    int32 boundsB;
    uint16 sfxBossHit;
    uint16 sfxExplosion2;
    uint16 sfxMagnet;
    uint16 sfxOrbinaut;
    uint16 aniFrames;
} ObjectBigSqueeze;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    BigSqueezeTypes type;
    int32 setupTimer;
    int32 invincibilityTimer;
    int32 timer;
    Entity *eggman;
    bool32 invincible;
    Animator animator;
    Animator domeAnimator;
    Animator prongsAnimator;
    Animator wheelAnimator;
    Animator electricAnimator;
    Hitbox hitbox;
} EntityBigSqueeze;

extern ObjectBigSqueeze *BigSqueeze;
void BigSqueeze_EnemyInfoHook(void);
Hitbox* BigSqueeze_GetHitbox(Entity* e);
void BigSqueeze_TakeHit(EntityPlayer* player, Entity* e);
extern void (*BigSqueeze_StateBoss_Idle)(void);
extern void (*BigSqueeze_StateBoss_Electrified)(void);
extern void (*BigSqueeze_HandleWallCollisions)(void);
extern void (*BigSqueeze_StateBoss_Destroyed)(void);

#endif //! OBJ_BIGSQUEEZE_H
