#include "MenuState.h"
#include "logging.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}
void MenuState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}
bool MenuState::onEnter()
{
    if(!TextureManager::Instance()->load("assets/button.png", "playbutton", Game::Instance()->getRenderer()))
    {
        return false;
    }
    if(!TextureManager::Instance()->load("assets/exit.png", "exitbutton", Game::Instance()->getRenderer()))
    {
        return false;
    }
    GameObject* button1 = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"), s_menuToPlay);
    GameObject* button2 = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"), s_exitFromMenu);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    DEBUG("entering MenuState");
    return true;
}
bool MenuState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TextureManager::Instance()->clearFromTextureMap("playbutton");
    TextureManager::Instance()->clearFromTextureMap("exitbutton");
    DEBUG("exiting MenuState");
    return true;
}

void MenuState::s_menuToPlay()
{
    DEBUG("Play button clicked");
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}
void MenuState::s_exitFromMenu()
{
    DEBUG("Exit button clicked");
    Game::Instance()->quit();
}