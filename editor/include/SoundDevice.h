#ifndef __SOURCE_DEVICE_H__
#define __SOURCE_DEVICE_H__
#include "AL/alc.h"

class SoundDevice
{
public:
	static SoundDevice* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new SoundDevice();
            return s_pInstance;
        }
        return s_pInstance;
    }
private:
	SoundDevice();
	~SoundDevice();
	static SoundDevice* s_pInstance;
	ALCdevice * p_ALCDevice;
	ALCcontext * p_ALCContext;
	SoundDevice * p_SoundDevice;
};

#endif //__SOURCE_DEVICE_H__