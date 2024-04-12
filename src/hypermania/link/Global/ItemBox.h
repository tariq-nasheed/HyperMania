#pragma once

// Object Struct
extern ObjectItemBox* ItemBox;

// Imported Functions
extern void (*ItemBox_State_Broken)();
extern void (*ItemBox_Break)(EntityItemBox* itemBox, EntityPlayer* player);