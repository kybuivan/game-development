#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "AnimatedGraphic.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    logconsoler.Init();
    int flags = 0;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK) >= 0)
    {
        DEBUG("SDL init success");
        // if succeeded create our window
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        // if the window creation succeeded create our renderer
        if(m_pWindow != 0)
        {
            DEBUG("window creation success");
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if(m_pRenderer != 0) // renderer init success
            {
                DEBUG("renderer creation success");
                SDL_SetRenderDrawColor(m_pRenderer,
                0, 0, 0, 255);
            }
            else
            {
                ERROR("renderer init fail");
                return false; // renderer init fail
            }
        }
        else
        {
            ERROR("window init fail");
            return false; // window init fail
        }
    }
    else
    {
        ERROR("SDL init fail");
        return false; // SDL init fail
    }

	m_gameWidth = width;
	m_gameHeight = height;
    InputHandler::Instance()->initialiseJoysticks();

    GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    GameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	GameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());

    DEBUG("init success");
    m_bRunning = true; // everything inited successfully, start the main loop
    return true;
}

void Game::render()
{
    // clear the window to black
    SDL_RenderClear(m_pRenderer);

    m_pGameStateMachine->render();

    // show the window
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    m_pGameStateMachine->update();
}

void Game::handleEvents()
{
    InputHandler::Instance()->update();
}

void Game::clean()
{
    DEBUG("cleaning game");
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
    logconsoler.Release();
}

void Game::quit()
{
    m_bRunning = false;
}