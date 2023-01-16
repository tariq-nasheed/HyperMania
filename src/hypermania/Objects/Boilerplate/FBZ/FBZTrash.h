#ifndef OBJ_FBZTRASH_H
#define OBJ_FBZTRASH_H

#include "GameAPI/Game.h"

typedef enum {
    FBZTRASH_TRASH,
    FBZTRASH_UNUSED,
    FBZTRASH_ORB,
    FBZTRASH_ORBINAUT,
} FBZTrashTypes;

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectFBZTrash;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    FBZTrashTypes type;
    int32 frameID;
    int32 rumbleMove;
    int32 timer;
    int32 radius;
    Vector2 targetPos;
    Vector2 startPos;
    void *parent;
    Hitbox hitbox;
    Animator animator;
} EntityFBZTrash;

extern ObjectFBZTrash *FBZTrash;
void FBZTrash_EnemyInfoHook(void);
extern void (*FBZTrash_State_OrbinautMove)(void);

#endif //! OBJ_FBZTRASH_H
