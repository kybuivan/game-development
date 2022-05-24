#ifndef __PLAY_STATE_H__
#define __PLAY_STATE_H__
#include "GameState.h"
class GameObject;
class SDLGameObject;

class PlayState : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const { return s_playID; }
    bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
private:
    static const std::string s_playID;

    std::vector<GameObject*> m_gameObjects;
};
#endif //__PLAY_STATE_H__