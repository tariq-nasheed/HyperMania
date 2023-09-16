#ifndef OBJ_INVINCIBLESTARS_H
#define OBJ_INVINCIBLESTARS_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
	RSDK_OBJECT
	uint16 aniFrames;
} ObjectInvincibleStars;

// Entity Class
typedef struct {
	RSDK_ENTITY
	EntityPlayer* player;
	Vector2 starPos[8];
	int32 starAngle[2];
	int32 starFrame[2];
	int32 starOffset;
	Animator starAnimator[4];
} EntityInvincibleStars;

extern ObjectInvincibleStars* InvincibleStars;

#endif //! OBJ_INVINCIBLESTARS_H