#ifndef OBJ_EXPLOSION_H
#define OBJ_EXPLOSION_H

#include "GameAPI/Game.h"

typedef enum {
    EXPLOSION_ITEMBOX,
    EXPLOSION_ENEMY,
    EXPLOSION_BOSS,
    EXPLOSION_BOSSPUFF,
} ExplosionTypes;

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxDestroy;
} ObjectExplosion;

typedef struct {
    RSDK_ENTITY
    Animator animator;
    int32 planeFilter;
} EntityExplosion;

extern ObjectExplosion *Explosion;

#endif //! OBJ_EXPLOSION_H
