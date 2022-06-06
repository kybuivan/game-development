#include "GameOverState.h"
#include "logging.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
    Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}
void GameOverState::s_restartPlay()
{
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameOverState::update()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->update();
        }
    }
}
void GameOverState::render()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}
bool GameOverState::onEnter()
{
    // parse the state
	StateParser stateParser;
	stateParser.parseState("assets/conan.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);
	
	// set the callbacks for menu items
	setCallbacks(m_callbacks);

    m_loadingComplete = true;
    return true;
}
bool GameOverState::onExit()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->clean();
            delete m_gameObjects[i];
        }
        
        m_gameObjects.clear();
    }

    // clear the texture manager
	for(int i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    InputHandler::Instance()->reset();
    
    DEBUG("exiting GameOverState");
    return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	// go through the game objects
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		// if they are of type MenuButton then assign a callback based on the id passed in from the file
		if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}