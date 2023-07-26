#ifndef OBJ_RING_H
#define OBJ_RING_H

#include "GameAPI/Game.h"
#include "Player.h"

typedef enum {
    RING_TYPE_NORMAL,
    RING_TYPE_BIG,
    RING_TYPE_SPARKLE1,
    RING_TYPE_SPARKLE2,
    RING_TYPE_SPARKLE3,
} RingTypes;

typedef enum {
    RING_MOVE_FIXED,
    RING_MOVE_LINEAR,
    RING_MOVE_CIRCLE,
    RING_MOVE_TRACK,
    RING_MOVE_PATH,
} RingMoveTypes;

typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    int32 pan;
    uint16 aniFrames;
    uint16 sfxRing;
} ObjectRing;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    RingTypes type;
    ManiaPlaneFilterTypes planeFilter;
    int32 ringAmount;
    int32 timer;
    int32 maxFrameCount;
    int32 sparkleType;
    EntityPlayer *storedPlayer;
    RingMoveTypes moveType;
    Vector2 amplitude;
    int32 speed;
    Vector2 drawPos;
    Animator animator;
} EntityRing;

extern ObjectRing *Ring;

// Imported Functions
extern void (*Ring_State_Lost)(void);
extern void (*Ring_Draw_Normal)(void);
extern void (*Ring_State_Sparkle)(void);
extern void (*Ring_Draw_Sparkle)(void);
extern void (*Ring_Collect)(void);

#define OBJ_RING_SETUP \
  IMPORT_PUBLIC_FUNC(Ring_State_Lost); \
  IMPORT_PUBLIC_FUNC(Ring_State_Lost); \
  IMPORT_PUBLIC_FUNC(Ring_State_Sparkle); \
  IMPORT_PUBLIC_FUNC(Ring_Draw_Sparkle); \
  IMPORT_PUBLIC_FUNC(Ring_Collect); \
  MOD_REGISTER_OBJECT_HOOK(Ring)

#endif //! OBJ_RING_H
