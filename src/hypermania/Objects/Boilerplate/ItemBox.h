#ifndef OBJ_ITEMBOX_H
#define OBJ_ITEMBOX_H

#include "GameAPI/Game.h"
#include "Player.h"

// Object Struct
extern ObjectItemBox *ItemBox;

// Imported Functions
extern void (*ItemBox_State_Broken)(void);
extern void (*ItemBox_Break)(EntityItemBox *itemBox, EntityPlayer *player);

#endif //! OBJ_ITEMBOX_H
