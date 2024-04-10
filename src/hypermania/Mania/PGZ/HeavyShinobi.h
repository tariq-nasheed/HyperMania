#ifndef OBJ_HEAVYSHINOBI_H
#define OBJ_HEAVYSHINOBI_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    int8 health;
    uint8 invincibilityTimer;
    Animator fxTrailAnimator[4];
    uint8 storedIDs[4];
    uint8 storedAnimIDs[4];
    Vector2 storePos[16];
    Animator unusedAnimator;
    uint8 activeShurikens;
    uint16 aniFrames;
    Hitbox hitboxShinobi;
    Hitbox hitboxSlashRange;
    Hitbox hitboxUnused;
    Hitbox hitboxSlash;
    Hitbox hitboxAsteron;
    Hitbox hitboxBounds;
    Hitbox hitboxAsteronSpike;
    uint16 sfxHit;
    uint16 sfxExplosion;
    uint16 sfxDefeat;
    uint16 sfxDropIn;
    uint16 sfxExplode;
    uint16 sfxGlitch;
    uint16 sfxJump;
    uint16 sfxParry;
    uint16 sfxSlash;
    uint16 sfxStick;
    uint16 sfxThrow;
} ObjectHeavyShinobi;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 type;
    int32 timer;
    int32 glitchTimer;
    EntityPlayer *playerPtr;
    Vector2 playerDistance;
    Animator mainAnimator;
    Animator fxAnimator;
} EntityHeavyShinobi;

extern ObjectHeavyShinobi* HeavyShinobi;

void HeavyShinobi_EnemyInfoHook(void);
extern void (*HeavyShinobi_State_Idle)();
extern void (*HeavyShinobi_State_Slash)();
extern void (*HeavyShinobi_State_Jump)();
extern void (*HeavyShinobi_State_Glitched)();
extern void (*HeavyShinobi_State_Destroyed)();

#define OBJ_HEAVYSHINOBI_SETUP \
  IMPORT_PUBLIC_FUNC(HeavyShinobi_State_Idle); \
  IMPORT_PUBLIC_FUNC(HeavyShinobi_State_Slash); \
  IMPORT_PUBLIC_FUNC(HeavyShinobi_State_Jump); \
  IMPORT_PUBLIC_FUNC(HeavyShinobi_State_Glitched); \
  IMPORT_PUBLIC_FUNC(HeavyShinobi_State_Destroyed); \
  REGISTER_ENEMY(HeavyShinobi)

#endif //! OBJ_HEAVYSHINOBI_H