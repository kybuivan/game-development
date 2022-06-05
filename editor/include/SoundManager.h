#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include <iostream>
#include <map>
#include <string>
//#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"
#include "AL/alc.h"

class SoundManager
{
public:
    
    static SoundManager* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new SoundManager();
            return s_pInstance;
        }
        return s_pInstance;
    }
    
    bool load(char const* fileName, std::string id);
    
    void playSound( std::string id);
    
private:

    static SoundManager* s_pInstance;
    //SoundDevice * p_SoundDevice;

    SoundManager();
    ~SoundManager();
    std::map< std::string, ALuint> m_sfxs;
    ALCdevice * p_ALCDevice;
	ALCcontext * p_ALCContext;
    SoundManager(const SoundManager&);
	SoundManager& operator=(const SoundManager&);
};
#endif //__SOUND_MANAGER_H__