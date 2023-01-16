#include "WeatherMobile.h"

ObjectTVPole *TVPole;
ObjectWeatherMobile *WeatherMobile;
void (*WeatherMobile_State_EnterEggman)(void);
void (*WeatherMobile_State_HandleMovement)(void);
void (*WeatherMobile_State_WindAttack)(void);
void (*WeatherMobile_State_SunAttack)(void);
void (*WeatherMobile_State_Defeated)(void);
void (*WeatherMobile_StateLights_Shine)(void);
void (*WeatherMobile_StateLights_DimAndDissapear)(void);
void (*WeatherMobile_StateCloud_FadeAway)(void);
void (*TVPole_State_ForceRelease)(void);

void WeatherMobile_EnemyInfoHook(void) {
	Mod.Super(WeatherMobile->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = WeatherMobile->classID;
	EnemyDefs[EnemyInfoSlot].animal = false;
	EnemyDefs[EnemyInfoSlot].boss = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = WeatherMobile_State_EnterEggman;
	EnemyDefs[EnemyInfoSlot].states[1].func = WeatherMobile_State_HandleMovement;
	EnemyDefs[EnemyInfoSlot].states[2].func = WeatherMobile_State_WindAttack;
	EnemyDefs[EnemyInfoSlot].states[3].func = WeatherMobile_State_SunAttack;
	EnemyDefs[EnemyInfoSlot].hitbox_func = WeatherMobile_GetHitbox;
	EnemyDefs[EnemyInfoSlot].destroy_func = WeatherMobile_TakeHit;
	++EnemyInfoSlot;
}

Hitbox* WeatherMobile_GetHitbox(Entity* e) {
	EntityWeatherMobile* self = (EntityWeatherMobile*)e;
	return &self->hitbox;
}

void WeatherMobile_TakeHit(EntityPlayer* player, Entity* e) {
	EntityWeatherMobile* self = (EntityWeatherMobile*)e;
	if (!self->invincibilityTimer) {
		if (--self->health <= 0) {
			RSDK.SetSpriteAnimation(WeatherMobile->eggmanFrames, 3, &self->eggmanAnimator, true, 0);
			self->state = WeatherMobile_State_Defeated;
			self->timer = 0;

			foreach_active(WeatherMobile, weatherMobile) {
				switch (weatherMobile->type) {
					case WEATHERMOBILE_LIGHTS:
					if (weatherMobile->state == WeatherMobile_StateLights_Shine) {
						weatherMobile->timer = 0;
						weatherMobile->state = WeatherMobile_StateLights_DimAndDissapear;
					}
					break;

					case WEATHERMOBILE_WIND_MANAGER:
					case WEATHERMOBILE_RAIN_MANAGER:
						destroyEntity(weatherMobile);
						Zone->cameraBoundsT[0] = Zone->cameraBoundsB[0] - ScreenInfo->size.y;
						break;

					case WEATHERMOBILE_CLOUD:
					if (weatherMobile->state != WeatherMobile_StateCloud_FadeAway) {
						weatherMobile->timer     = 0;
						weatherMobile->stateDraw = StateMachine_None;
						weatherMobile->state     = WeatherMobile_StateCloud_FadeAway;
					}
					break;

					default: break;
				}
			}

			foreach_active(TVPole, pole) { pole->state = TVPole_State_ForceRelease; }
			SceneInfo->timeEnabled = false;
			Player_GiveScore(RSDK_GET_ENTITY(SLOT_PLAYER1, Player), 1000);
		} else {
			self->invincibilityTimer = 48;
			RSDK.SetSpriteAnimation(WeatherMobile->eggmanFrames, 2, &self->eggmanAnimator, true, 0);
			RSDK.PlaySfx(WeatherMobile->sfxHit, false, 255);
		}
	}
}