#ifndef __SOUND_BUFFER_H__
#define __SOUND_BUFFER_H__
#include "AL/al.h"
#include <vector>
class SoundBuffer
{
public:
	static SoundBuffer* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new SoundBuffer();
            return s_pInstance;
        }
        return s_pInstance;
    }

	ALuint addSoundEffect(const char* filename) noexcept;
	bool removeSoundEffect(const ALuint& buffer) noexcept;

private:
	SoundBuffer();
	~SoundBuffer();
	static SoundBuffer* s_pInstance;
	std::vector<ALuint> p_SoundEffectBuffers;
};

#endif //__SOUND_BUFFER_H__