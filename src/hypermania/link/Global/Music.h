#pragma once

extern ObjectMusic *Music;

extern void (*Music_PlayTrack)(uint8 trackID);
extern void (*Music_SetMusicTrack)(const char* path, uint8 track, uint32 loopPoint);
extern void (*Music_FadeOut)(float fadeSpeed);
extern void (*Music_PlayJingle)(uint8 trackID);

#define OBJ_MUSIC_SETUP \
  IMPORT_PUBLIC_FUNC(Music_PlayTrack); \
  IMPORT_PUBLIC_FUNC(Music_SetMusicTrack); \
  IMPORT_PUBLIC_FUNC(Music_FadeOut); \
  IMPORT_PUBLIC_FUNC(Music_PlayJingle); \
  MOD_REGISTER_OBJECT_HOOK(Music)