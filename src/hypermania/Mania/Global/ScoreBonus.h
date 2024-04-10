#ifndef MANIA_SCOREBONUS_H
#define MANIA_SCOREBONUS_H

typedef struct {
	RSDK_OBJECT
	uint16 aniFrames;
} ObjectScoreBonus;

typedef struct {
	RSDK_ENTITY
	int32 timer;
	Animator animator;
} EntityScoreBonus;

extern ObjectScoreBonus* ScoreBonus;

#endif //! MANIA_SCOREBONUS_H