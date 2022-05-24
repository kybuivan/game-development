#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "SDLGameObject.h"
#include "GameObjectFactory.h"
#include "LoaderParams.h"

class Player : public SDLGameObject
{
public:
    Player();
    void draw();
    void update();
    void clean(){}

    void load(const LoaderParams* pParams);
private:
    void handleInput();
};

class PlayerCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Player();
    }
};
#endif //__PLAYER_H__