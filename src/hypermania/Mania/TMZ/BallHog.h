#pragma once

struct ObjectBallHog {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxBomb;
    uint16 aniFrames;
    uint16 sfxExplosion;
    uint16 sfxArrowHit;
    uint16 sfxDrop;
    uint16 sfxJump;
};

struct EntityBallHog {
    RSDK_ENTITY
    StateMachine(state);
    uint8 numJumps;
    uint8 bombTime;
    uint8 timer;
    uint8 jumpCount;
    Vector2 startPos;
    uint8 startDir;
    Animator animator;
};
