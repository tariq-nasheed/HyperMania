#ifndef OBJ_UFO_PLAYER_H
#define OBJ_UFO_PLAYER_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    int32 maxSpeed;
    uint16 aniFrames; // unused
    uint16 sfxJump;
    uint16 sfxCharge;
    uint16 sfxRelease;
    uint16 sfxLoseRings;
    uint16 sfxDrop;
    uint16 sfxBumper;
    uint16 sfxSpring;
    uint16 sfxSkid;
    uint16 sfxGrittyGround;
    uint16 jogModel;
    uint16 dashModel;
    uint16 jumpModel;
    uint16 ballModel;
    uint16 tumbleModel;
    uint16 sceneIndex;
} ObjectUFO_Player;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 machQuota1;
    int32 machQuota2;
    int32 machQuota3;
    int32 startingRings;
    int32 timer;
    int32 courseOutTimer;
    int32 angleX;
    int32 height;
    int32 gravityStrength;
    int32 angleZ;
    int32 velDivisor;
    int32 bumperTimer;
    int32 angleVel;
    int32 skidTimer;
    Entity *camera;
    Entity *circuitPtr;
    Matrix matRotate;
    Matrix matTransform;
    Matrix matWorld;
    Matrix matNormal;
    StateMachine(stateInput);
    int32 controllerID;
    bool32 up;
    bool32 down;
    bool32 left;
    bool32 right;
    bool32 jumpPress;
    bool32 jumpHold;
    Animator animator;
} EntityUFO_Player;

extern ObjectUFO_Player *UFO_Player;

bool32 UFO_Player_State_UFOCaught_Released_HOOK(bool32);

#define OBJ_UFO_PLAYER_SETUP \
  HOOK_STATE(UFO_Player_State_UFOCaught_Released, 1); \
  MOD_REGISTER_OBJECT_HOOK(UFO_Player)

#endif //! OBJ_UFO_PLAYER_H
