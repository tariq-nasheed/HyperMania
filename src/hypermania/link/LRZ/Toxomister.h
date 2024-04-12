extern ObjectToxomister* Toxomister;

extern void (*Toxomister_State_CreateClouds)();

void Toxomister_EnemyInfoHook();

#define OBJ_TOXOMISTER_SETUP \
  IMPORT_PUBLIC_FUNC(Toxomister_State_CreateClouds); \
  REGISTER_ENEMY(Toxomister)