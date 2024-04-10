#include "WeatherMobile.h"

ObjectWeatherMobile* WeatherMobile;
void (*WeatherMobile_State_EnterEggman)();
void (*WeatherMobile_State_HandleMovement)();
void (*WeatherMobile_State_WindAttack)();
void (*WeatherMobile_State_SunAttack)();
void (*WeatherMobile_Hit)();

bool32 WeatherMobile_CheckVulnerable(Entity* self) {
	if (((EntityWeatherMobile*)self)->invincibilityTimer) return false;
	return (
	    ((EntityWeatherMobile*)self)->state == WeatherMobile_State_EnterEggman
	 || ((EntityWeatherMobile*)self)->state == WeatherMobile_State_HandleMovement
	 || ((EntityWeatherMobile*)self)->state == WeatherMobile_State_WindAttack
	 || ((EntityWeatherMobile*)self)->state == WeatherMobile_State_SunAttack
	);
}

Hitbox* WeatherMobile_GetHitbox(Entity* self) { return &(((EntityWeatherMobile*)self)->hitbox); }

void WeatherMobile_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	WeatherMobile_Hit();
	SceneInfo->entity = old_entity;
}

void WeatherMobile_EnemyInfoHook() {
	Mod.Super(WeatherMobile->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(WeatherMobile->classID, WeatherMobile_CheckVulnerable, WeatherMobile_GetHitbox, WeatherMobile_OnHit, NULL, ATKFLAG_ISBOSS);
}