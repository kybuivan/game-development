#include "PauseState.h"
#include "logging.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "StateParser.h"
#include "InputHandler.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
    Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}
void PauseState::s_resumePlay()
{
    Game::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->update();
        }
    }
}
void PauseState::render()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}
bool PauseState::onEnter()
{
    StateParser stateParser;
	stateParser.parseState("assets/attack.xml", s_pauseID, &m_gameObjects, &m_textureIDList);
	
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);
	
	setCallbacks(m_callbacks);

    m_loadingComplete = true;
    
    DEBUG("entering PauseState");
    return true;
}
bool PauseState::onExit()
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

    // reset the mouse button states to false
	InputHandler::Instance()->reset();

    DEBUG("exiting PauseState");
    return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
{
    // go through the game objects
    if(!m_gameObjects.empty())
    {
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
}