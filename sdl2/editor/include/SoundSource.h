#ifndef __SOUND_SOURCE_H__
#define __SOUND_SOURCE_H__
#include "AL/al.h"
class SoundSource
{
public:
    SoundSource();
    ~SoundSource();

    void Play(const ALuint buffer_to_play) noexcept;

private:
    ALuint p_Source;
    float p_Pitch = 1.f;
    float p_Gain = 1.f;
    float p_Position[3] = { 0,0,0 };
    float p_Velocity[3] = { 0,0,0 };
    bool p_LoopSound = false;
    ALuint p_Buffer = 0;
};

#endif //__SOUND_SOURCE_H__