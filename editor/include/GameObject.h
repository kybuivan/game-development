#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__
#include <SDL.h>
#include "LoaderParams.h"

class GameObject
{
public:
    virtual void draw()=0;
    virtual void update()=0;
    virtual void clean()=0;

    // new load function
    virtual void load(const LoaderParams* pParams)=0;
protected:
    GameObject() {}
    virtual ~GameObject() {}

    std::string m_textureID;
};
#endif //__GAME_OBJECT_H__