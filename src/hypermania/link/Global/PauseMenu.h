#pragma once

extern ObjectPauseMenu *PauseMenu;

#define OBJ_PAUSEMENU_SETUP \
  MOD_REGISTER_OBJECT_HOOK(PauseMenu)