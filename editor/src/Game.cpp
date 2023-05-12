#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "SoundBuffer.h"

Game* Game::s_pInstance = 0;

Game::Game()
    : m_pWindow(0)
    , m_pRenderer(0)
    , m_bRunning(false)
    , m_pGameStateMachine(0)
    , m_playerLives(3)
    , m_bLevelComplete(false)
    , m_currentLevel(1)
{
}

Game::~Game()
{
    // we must clean up after ourselves to prevent memory leaks
    m_pRenderer= 0;
    m_pWindow = 0;
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    logconsoler.Init();
    int flags = 0;
    m_gameWidth = width;
    m_gameHeight = height;

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
    
    // start the menu state
    m_pGameStateMachine = new GameStateMachine();

    DEBUG("init success");
    m_bRunning = true; // everything inited successfully, start the main loop
    return true;
}

void Game::setCurrentLevel(int currentLevel)
{
    m_currentLevel = currentLevel;
    m_pGameStateMachine->changeState(new GameOverState());
    m_bLevelComplete = false;
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
    InputHandler::Instance()->clean();
    m_pGameStateMachine->clean();
    m_pGameStateMachine = 0;
    delete m_pGameStateMachine;
    TextureManager::Instance()->clearTextureMap();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
    logconsoler.Release();
}

void Game::quit()
{
    m_bRunning = false;
}