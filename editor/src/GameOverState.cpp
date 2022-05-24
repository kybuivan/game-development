#include "GameOverState.h"
#include "logging.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
    Game::Instance()->getStateMachine()->changeState(new MenuState());
}
void GameOverState::s_restartPlay()
{
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameOverState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}
void GameOverState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}
bool GameOverState::onEnter()
{
    if(!TextureManager::Instance()->load("assets/gameover.png", "gameoverbutton", Game::Instance()->getRenderer()))
    {
        return false;
    }
    if(!TextureManager::Instance()->load("assets/main.png", "mainbutton", Game::Instance()->getRenderer()))
    {
        return false;
    }
    if(!TextureManager::Instance()->load("assets/restart.png", "restartbutton", Game::Instance()->getRenderer()))
    {
        return false;
    }
    GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 190, 30, "gameoverbutton"), 2);
    GameObject* button1 = new MenuButton(new LoaderParams(200, 200, 200, 80, "mainbutton"), s_gameOverToMain);
    GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "restartbutton"), s_restartPlay);
    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    DEBUG("entering GameOverState");
    return true;
}
bool GameOverState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TextureManager::Instance()->clearFromTextureMap("mainbutton");
    TextureManager::Instance()->clearFromTextureMap("resumebutton");
    DEBUG("exiting GameOverState");
    return true;
}