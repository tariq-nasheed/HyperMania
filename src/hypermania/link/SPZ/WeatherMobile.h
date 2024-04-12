#pragma once

extern ObjectWeatherMobile* WeatherMobile;

extern void (*WeatherMobile_State_EnterEggman)();
extern void (*WeatherMobile_State_HandleMovement)();
extern void (*WeatherMobile_State_WindAttack)();
extern void (*WeatherMobile_State_SunAttack)();
extern void (*WeatherMobile_Hit)();

void WeatherMobile_EnemyInfoHook();

#define OBJ_WEATHERMOBILE_SETUP \
  IMPORT_PUBLIC_FUNC(WeatherMobile_State_EnterEggman); \
  IMPORT_PUBLIC_FUNC(WeatherMobile_State_HandleMovement); \
  IMPORT_PUBLIC_FUNC(WeatherMobile_State_WindAttack); \
  IMPORT_PUBLIC_FUNC(WeatherMobile_State_SunAttack); \
  IMPORT_PUBLIC_FUNC(WeatherMobile_Hit); \
  REGISTER_ENEMY(WeatherMobile)