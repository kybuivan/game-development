#ifndef __GAME_H__
#define __GAME_H__
#include <SDL.h>
#include "logging.h"
#include "SDLGameObject.h"
#include "GameStateMachine.h"
#include <vector>

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
    SDL_Window* getWindow() const { return m_pWindow; }
    GameStateMachine* getStateMachine(){ return m_pGameStateMachine; }
	
    void setPlayerLives(int lives) { m_playerLives = lives; }
    int getPlayerLives() { return m_playerLives; }
    
    void setCurrentLevel(int currentLevel);
    const int getCurrentLevel() { return m_currentLevel; }
    
    void setNextLevel(int nextLevel) { m_nextLevel = nextLevel; }
    const int getNextLevel() { return m_nextLevel; }
    
    void setLevelComplete(bool levelComplete) { m_bLevelComplete = levelComplete; }
    const bool getLevelComplete() { return m_bLevelComplete; }

	int getGameWidth() const { return m_gameWidth; }
	int getGameHeight() const { return m_gameHeight; }
    
    float getScrollSpeed() { return m_scrollSpeed; }

	bool changingState() { return m_bChangingState; }
	void changingState(bool cs) { m_bChangingState = cs; }
    
    std::vector<std::string> getLevelFiles() { return m_levelFiles; }

    private:
    Game();
	Game(const Game&);
	Game& operator=(const Game&);
	~Game();
    // create the s_pInstance member variable
    bool m_bChangingState;
    static Game* s_pInstance;

    SDL_Window* m_pWindow = 0;
    SDL_Renderer* m_pRenderer = 0;

    //add an object of our GameStateMachine
    GameStateMachine* m_pGameStateMachine;
    bool m_bRunning;
	int m_gameWidth;
	int m_gameHeight;
    LogManager logconsoler;

    float m_scrollSpeed;
    
    int m_playerLives;
    
    int m_currentLevel;
    int m_nextLevel;
    bool m_bLevelComplete;
    
    std::vector<std::string> m_levelFiles;
};
#endif //__GAME_H__