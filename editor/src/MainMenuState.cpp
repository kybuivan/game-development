#include "MainMenuState.h"
#include "logging.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update()
{
    if(m_loadingComplete && !m_gameObjects.empty() && !m_exiting)
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->update();
        }
        
        //        if(InputHandler::Instance()->getButtonState(0, 8))
        //        {
        //            s_menuToPlay();
        //        }
    }
}

void MainMenuState::render()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool MainMenuState::onEnter()
{
    // parse the state
    StateParser stateParser;
    stateParser.parseState("assets/conan.xml", s_menuID, &m_gameObjects, &m_textureIDList);
    
    m_callbacks.push_back(0); //pushback 0 callbackID start from 1
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
    
    m_loadingComplete = true;
    DEBUG("entering MenuState");
    
    return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
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

bool MainMenuState::onExit()
{
	m_exiting = true;
    
    // clean the game objects
    if(m_loadingComplete && !m_gameObjects.empty())
    {
		m_gameObjects.back()->clean();
		m_gameObjects.pop_back();
    }
    m_gameObjects.clear();
    
	/* clear the texture manager
	for(int i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	*/
	
    //TextureManager::Instance()->clearFromTextureMap("exitbutton");
	
	// reset the input handler
    InputHandler::Instance()->reset();
    DEBUG("exiting MenuState");
    return true;
}

void MainMenuState::s_menuToPlay()
{
    DEBUG("Play button clicked");
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}
void MainMenuState::s_exitFromMenu()
{
    DEBUG("Exit button clicked");
    Game::Instance()->quit();
}