#pragma once

extern ObjectGrabber* Grabber;

void Grabber_EnemyInfoHook();

#define OBJ_GRABBER_SETUP \
  REGISTER_ENEMY(Grabber)