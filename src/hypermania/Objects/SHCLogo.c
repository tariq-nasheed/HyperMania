#include "LogoSetup.h"
#include "SHCLogo.h"

ObjectSHCLogo* SHCLogo;

void SHCLogo_Update() {}
void SHCLogo_LateUpdate() {}
void SHCLogo_StaticUpdate() {}

void SHCLogo_Draw() {
	RSDK_THIS(SHCLogo);

	RSDK.DrawSprite(&self->animator, &self->position, false);
	RSDK.ProcessAnimation(&self->animator);
}

void SHCLogo_Create(void* data) {
	RSDK_THIS(SHCLogo);

	RSDK.SetSpriteAnimation(SHCLogo->aniFrames, 0, &self->animator, true, 0);
	self->visible   = true;
	self->drawGroup = 2;
	self->active    = ACTIVE_BOUNDS;
}

void SHCLogo_StageLoad() {
	SHCLogo->aniFrames = RSDK.LoadSpriteAnimation("Logos/Splash.bin", SCOPE_STAGE);
	SHCLogo->sfxSplash = RSDK.GetSfx("Logos/SHCSplash.wav");
}

#if RETRO_INCLUDE_EDITOR
void SHCLogo_EditorDraw() {}
void SHCLogo_EditorLoad() {}
#endif
void SHCLogo_Serialize() {}

bool32 LogoSetup_State_FadeToNextLogos_HOOK(bool32 skippedState) {
	if (skippedState) return true;
	RSDK_THIS(LogoSetup);

	const int32 target = (ScreenInfo->position.y == SCREEN_YSIZE) ? 240 : 120;
	if (++self->timer > target || (self->timer > 30 && ControllerInfo->keyStart.press)) {
		self->timer     = 0;
		self->state     = LogoSetup_State_NextLogos;
		self->stateDraw = LogoSetup_Draw_Fade;
	}
	return true;
}

bool32 LogoSetup_State_ShowLogos_HOOK(bool32 skippedState) {
	if (skippedState) return true;
	RSDK_THIS(LogoSetup);

	 if (self->timer <= 0) {
		if (ScreenInfo->position.y == SCREEN_YSIZE) {
			RSDK.PlaySfx(SHCLogo->sfxSplash, 0, 0xFF);
		}
		foreach_active(SHCLogo, shcLogo) {
			shcLogo->animator.frameID = 0;
		}
	}
	return false;
}

bool32 LogoSetup_State_NextLogos_HOOK(bool32 skippedState) {
	if (skippedState) return true;
	RSDK_THIS(LogoSetup);

	if (self->timer >= 1024) {
		if (ScreenInfo->position.y >= SCREEN_YSIZE * 2) {
			++SceneInfo->listPos;
			RSDK.LoadScene();
		} else {
			ScreenInfo->position.y += SCREEN_YSIZE;
			self->state     = LogoSetup_State_ShowLogos;
			self->stateDraw = LogoSetup_Draw_Fade;
			self->timer     = 0x400;
		}
	} else {
		if (ScreenInfo->position.y == SCREEN_YSIZE) {
			foreach_active(SHCLogo, shcLogo) {
				shcLogo->animator.speed   = 0;
				shcLogo->animator.frameID = 0;
			}
		}
		self->timer += 16;
	}
	return true;
}