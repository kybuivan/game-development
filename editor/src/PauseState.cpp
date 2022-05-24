#include "PauseState.h"
#include "logging.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"
#include "MenuButton.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
    Game::Instance()->getStateMachine()->changeState(new MenuState());
}
void PauseState::s_resumePlay()
{
    Game::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}
void PauseState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}
bool PauseState::onEnter()
{
    if(!TextureManager::Instance()->load("assets/resume.png", "resumebutton", Game::Instance()->getRenderer()))
    {
        return false;
    }
    if(!TextureManager::Instance()->load("assets/main.png", "mainbutton", Game::Instance()->getRenderer()))
    {
        return false;
    }
    GameObject* button1 = new MenuButton(new LoaderParams(200, 100, 200, 80, "mainbutton"), s_pauseToMain);
    GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "resumebutton"), s_resumePlay);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    DEBUG("entering PauseState");
    return true;
}
bool PauseState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TextureManager::Instance()->clearFromTextureMap("mainbutton");
    TextureManager::Instance()->clearFromTextureMap("resumebutton");
    DEBUG("exiting PauseState");
    return true;
}