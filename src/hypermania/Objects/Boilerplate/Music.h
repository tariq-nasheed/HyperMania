#ifndef OBJ_MUSIC_H
#define OBJ_MUSIC_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    char trackNames[16][32];
    uint32 trackLoops[16];
    int32 trackStartPos;
    int32 channelID;
    int32 activeTrack;
#if MANIA_USE_PLUS
    int32 nextTrack;
    int32 restartTrackID;
#else
    int32 prevTrack;
    int32 queuedTrack;
    int32 nextTrack;
    bool32 playingRegularTrack;
    bool32 playingDrownTrack;
    bool32 playing1UPTrack;
#endif
    uint16 aniFrames;
} ObjectMusic;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    String trackFile;
    String soundTestTitle;
    int32 trackID;
    uint32 trackLoop;
    bool32 playOnLoad;
    bool32 restartTrack;
    int32 timer;
    int32 trackPriority;
    int32 trackStartPos;
    float volume;
    float fadeSpeed;
    Animator animator;
} EntityMusic;

extern ObjectMusic *Music;

extern void (*Music_FadeOut)(float fadeSpeed);
extern void (*Music_PlayJingle)(uint8 trackID);

#endif //! OBJ_MUSIC_H
