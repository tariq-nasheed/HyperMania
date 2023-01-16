#ifndef OBJ_DDWRECKER_H
#define OBJ_DDWRECKER_H

#include "GameAPI/Game.h"

typedef enum {
    DDWRECKER_SETUP,
    DDWRECKER_BALL1,
    DDWRECKER_BALL2,
    DDWRECKER_CHAIN,
    DDWRECKER_CORE,
} DDWreckerTypes;

typedef struct {
    RSDK_OBJECT
    int32 camBoundL;
    int32 camBoundR;
    int32 bossBoundL;
    int32 bossBoundR;
    int32 bossBoundT;
    int32 attackVelocities[3];
    TABLE(int32 spinOffset[6], { -64, -32, -16, 16, 32, 64 });
    TABLE(int32 swingOffset[6], { 32, 48, 64, 80, 96, 128 });
    uint16 aniFrames;
    uint16 sfxBossHit;
    uint16 sfxExplosion;
    uint16 sfxDrop;
    uint16 sfxImpact;
    uint16 sfxAssemble;
    uint16 sfxRotate;
    uint16 sfxSharp;
} ObjectDDWrecker;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateBall);
    Vector2 originPos;
    int32 type;
    int32 timer;
    int32 invincibilityTimer;
    int32 health;
    bool32 swapBalls;
    int32 angleVel;
    int32 spinTimer;
    int32 spinAngle;
    int32 radius;
    uint16 siblingSlots[6];
    Entity *bodyA;
    Entity *bodyB;
    int32 unused1;
    int32 unusedAngle; // updated but never used..
    int32 unused2;
    int32 unused3;
    int32 blendAmount;
    Animator animator;
    Hitbox hitbox;
} EntityDDWrecker;

extern ObjectDDWrecker *DDWrecker;

void DDWrecker_EnemyInfoHook(void);
bool32 DDWrecker_CheckVulnerable(Entity* e);
Hitbox* DDWrecker_GetHitbox(Entity* e);
void DDWrecker_TakeHit(EntityPlayer* player, Entity* e);
extern void (*DDWrecker_StateBall_Vulnerable)(void);
extern void (*DDWrecker_StateBall_Partnerless)(void);
extern void (*DDWrecker_StateBall_Spiked)(void);
extern void (*DDWrecker_State_Die)(void);
extern void (*DDWrecker_State_EndBounceAttack)(void);
extern void (*DDWrecker_State_Debris)(void);

#endif //! OBJ_DDWRECKER_H
