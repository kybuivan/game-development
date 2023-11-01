#include "SoundManager.h"
#include "logging.h"

SoundManager* SoundManager::s_pInstance = 0;

SoundManager::SoundManager()
{
    DEBUG("SoundManager instance");
    
    p_ALCDevice = alcOpenDevice(NULL); // nullptr = get default device
    if (p_ALCDevice == nullptr)
    {
        ERROR("Failed to get sound device");
    }

    p_ALCContext = alcCreateContext(p_ALCDevice, NULL);  // create context
    if(p_ALCContext == nullptr)
    {
        ERROR("Failed to set sound context");
    }

    if (!alcMakeContextCurrent(p_ALCContext))   // make context current
    {
        ERROR("Failed to make context current");
    }

    const ALCchar* name = nullptr;
    if (alcIsExtensionPresent(p_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
        name = alcGetString(p_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
    if (!name || alcGetError(p_ALCDevice) != AL_NO_ERROR)
        name = alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);
    DEBUG("Opened \"{}\"", name);
}

SoundManager::~SoundManager()
{
    if (!alcMakeContextCurrent(nullptr))
    {
        ERROR("failed to set context to nullptr");
    }

    alcDestroyContext(p_ALCContext);
    if (p_ALCContext)
    {
        ERROR("failed to unset during close");
    }

    if (!alcCloseDevice(p_ALCDevice))
    {
        ERROR("failed to close sound device");
    }
}

bool SoundManager::load(char const* fileName, std::string id)
{
    DEBUG("SoundManager load filename: {}, id={}", fileName, id);
    uint32_t /*ALuint*/ sound1 = SoundBuffer::Instance()->addSoundEffect(fileName);

    if(sound1 == NULL)
    {
        return false;
    }
    m_sfxs[id] = sound1;
    return true;
}

void SoundManager::playSound(std::string id)
{
    SoundSource mySpeaker;

    mySpeaker.Play(m_sfxs[id]);
}
