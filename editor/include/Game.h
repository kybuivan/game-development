#ifndef __GAME_H__
#define __GAME_H__
#include <SDL.h>
#include "logging.h"
#include "SDLGameObject.h"
#include "GameStateMachine.h"

class Game
{
    public:
    // create the public instance function
    static Game* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }
        
        return s_pInstance;
    }
    ~Game() {}
    // simply set the running variable to true
    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void render();
    void update();
    void handleEvents();
    void clean();
    void quit();
    // a function to access the private running variable
    bool running() { return m_bRunning; }
    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    
    GameStateMachine* getStateMachine(){ return m_pGameStateMachine; }
	
	int getGameWidth() const { return m_gameWidth; }
	
	int getGameHeight() const { return m_gameHeight; }
    
    private:
    Game(){}
    // create the s_pInstance member variable
    static Game* s_pInstance;

    SDL_Window* m_pWindow = 0;
    SDL_Renderer* m_pRenderer = 0;

    //add an object of our GameStateMachine
    GameStateMachine* m_pGameStateMachine;
    bool m_bRunning;
	int m_gameWidth;
	int m_gameHeight;
    LogManager logconsoler;
};
#endif //__GAME_H__