#pragma once

// Object Class
typedef struct {
	RSDK_OBJECT
	uint16 aniFrames;
	uint16 sfxImpact;
	uint16 sfxLedgeBreak;
} ObjectHPZBeam;

// Entity Class
typedef struct {
	RSDK_ENTITY
	int32 hit_timer;
	int32 target_y;
	int32 top;
	Animator topAnimator;
	Animator middleAnimator;
	Animator bottomAnimator;
} EntityHPZBeam;

// Object Struct
extern ObjectHPZBeam* HPZBeam;

// Standard Entity Events
void HPZBeam_Update(void);
void HPZBeam_LateUpdate(void);
void HPZBeam_StaticUpdate(void);
void HPZBeam_Draw(void);
void HPZBeam_Create(void *data);
void HPZBeam_StageLoad(void);
void HPZBeam_EditorDraw(void);
void HPZBeam_EditorLoad(void);
void HPZBeam_Serialize(void);