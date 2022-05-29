#ifndef __PLAY_STATE_H__
#define __PLAY_STATE_H__
#include "GameState.h"
#include "Level.h"
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
private:
    bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
    static const std::string s_playID;
    Level* m_pLevel;
    std::vector<GameObject*> m_gameObjects;
};
#endif //__PLAY_STATE_H__