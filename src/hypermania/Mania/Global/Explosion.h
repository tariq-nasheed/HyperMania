#pragma once

typedef enum {
    EXPLOSION_ITEMBOX,
    EXPLOSION_ENEMY,
    EXPLOSION_BOSS,
    EXPLOSION_BOSSPUFF,
} ExplosionTypes;

struct ObjectExplosion {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxDestroy;
};

struct EntityExplosion {
    RSDK_ENTITY
    Animator animator;
    int32 planeFilter;
};
