#include "Game.h"
#include "TextureManager.h"
#include "SDLGameObject.h"
#include "InputHandler.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen)
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
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
        // if the window creation succeeded create our renderer
        if(m_pWindow != 0)
        {
            DEBUG("window creation success");
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if(m_pRenderer != 0) // renderer init success
            {
                DEBUG("renderer creation success");
                SDL_SetRenderDrawColor(m_pRenderer,
                255, 0, 0, 255);
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

    // to load
    if(!TextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer))
    {
        ERROR("load texture fail");
        return false;
    }

    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(0, 0, 128, 82, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(200, 200, 128, 82, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "animate")));

    InputHandler::Instance()->initialiseJoysticks();

    DEBUG("init success");
    m_bRunning = true; // everything inited successfully, start the main loop
    return true;
}

void Game::render()
{
    // clear the window to black
    SDL_RenderClear(m_pRenderer);

    for(std::vector<GameObject*>::size_type i = 0; i !=
    m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }

    // show the window
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    for(std::vector<GameObject*>::size_type i = 0; i !=
    m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
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