#include "Music.h"

ObjectMusic *Music;
void (*Music_SetMusicTrack)(const char* path, uint8 track, uint32 loopPoint);
void (*Music_FadeOut)(float fadeSpeed);
void (*Music_PlayJingle)(uint8 trackID);
void (*Music_Stop)(void);