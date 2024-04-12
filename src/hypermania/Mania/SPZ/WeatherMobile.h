#pragma once

typedef enum {
	WEATHERMOBILE_EGGMAN,
	WEATHERMOBILE_LIGHTS,
	WEATHERMOBILE_WIND_MANAGER,
	WEATHERMOBILE_WIND,
	WEATHERMOBILE_RAIN_MANAGER,
	WEATHERMOBILE_RAIN,
	WEATHERMOBILE_CLOUD,
} WeatherMobileTypes;

struct ObjectWeatherMobile {
	RSDK_OBJECT
	TABLE(int32 debrisInfo[29], { 4,        0, 0, -0x20000, -0x28000, 1, 0, -0x20000, -0x28000, 2, 0, 0x20000, -0x20000, 3, 0, 0x28000,
	                              -0x20000, 4, 0, -0x10000, -0x10000, 5, 0, 0x10000,  -0x10000, 6, 0, -0x8000, -0x10000 });
	int32 boundsL;
	int32 boundsR;
	int32 boundsM;
	int32 boundsT;
	int32 boundsB;
	int32 currentAttack;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxCloud;
	uint16 sfxLightning;
	uint16 sfxSun;
	uint16 sfxWind;
	bool32 playingWindSfx;
	int32 windSfxChannel;
	int32 windSfxTimer;
	uint16 sfxRain;
	bool32 playingRainSfx;
	uint16 aniFrames;
	uint16 eggmanFrames;
};

struct EntityWeatherMobile {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	int32 type;
	int32 timer;
	int32 invincibilityTimer;
	int32 health;
	int32 lightsTimer;
	Vector2 origin;
	Entity* parent;
	Entity* weatherTV;
	Animator mainAnimator;
	Animator seatAnimator;
	Animator eggmanAnimator;
	Animator eggMobileAnimator;
	Animator decorAnimator;
	Animator radarDishLAnimator;
	Animator radarDishRAnimator;
	Hitbox hitbox;
};
