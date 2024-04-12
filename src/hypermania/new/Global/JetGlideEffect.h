#pragma once

// Object Class
typedef struct {
	RSDK_OBJECT
	uint16 aniFrames;
} ObjectJetGlideEffect;

// Entity Class
typedef struct {
	RSDK_ENTITY
	Animator animator;
	int32 timer;
	int32 dustCount;
	int32 sparkleCount;
	int32 rndOffset;
	int32 rndOffset2;
	int32 rndTable[256];
} EntityJetGlideEffect;

// Object Struct
extern ObjectJetGlideEffect* JetGlideEffect;

// Standard Entity Events
void JetGlideEffect_Update();
void JetGlideEffect_LateUpdate();
void JetGlideEffect_StaticUpdate();
void JetGlideEffect_Draw();
void JetGlideEffect_Create(void* data);
void JetGlideEffect_StageLoad();
void JetGlideEffect_EditorDraw();
void JetGlideEffect_EditorLoad();
void JetGlideEffect_Serialize();