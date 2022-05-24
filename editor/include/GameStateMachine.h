#ifndef __GAME_STATE_MACHINE_H__
#define __GAME_STATE_MACHINE_H__

#include <vector>
#include "GameState.h"

class GameStateMachine
{
public:
    
    GameStateMachine() {}
    ~GameStateMachine() {}
    
    void update();
    void render();
    
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    
    void clean();

	std::vector<GameState*>& getGameStates() { return m_gameStates; }

private:
    std::vector<GameState*> m_gameStates;
};

#endif //__GAME_STATE_MACHINE_H__
