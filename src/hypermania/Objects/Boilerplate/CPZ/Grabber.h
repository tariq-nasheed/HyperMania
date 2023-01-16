#ifndef OBJ_GRABBER_H
#define OBJ_GRABBER_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxGrab;
    Hitbox hitboxRange;
    uint16 aniFrames;
    uint16 sfxGrab;
    uint16 sfxDestroy;
} ObjectGrabber;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Animator bodyAnimator;
    Animator clampAnimator;
    Animator wheelAnimator;
    EntityPlayer *grabbedPlayer;
    uint16 struggleDelay;
    uint16 struggleTimer;
    uint16 struggleFlags;
    uint16 grabDelay;
    Vector2 startPos;
    uint8 startDir;
    int32 turnTimer;
    int32 timer;
} EntityGrabber;

extern ObjectGrabber *Grabber;
void Grabber_EnemyInfoHook(void);
extern void (*Grabber_State_CheckForGrab)(void);
extern void (*Grabber_State_GrabDelay)(void);
extern void (*Grabber_State_HandleTurn)(void);
extern void (*Grabber_State_TryToGrab)(void);
extern void (*Grabber_State_RiseUp)(void);
extern void (*Grabber_State_GrabbedPlayer)(void);
extern void (*Grabber_State_Struggle)(void);
extern void (*Grabber_State_PlayerEscaped)(void);

#endif //! OBJ_GRABBER_H
