#include "PlayState.h"
#include "logging.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "LevelParser.h"
#include "Level.h"
#include "BulletHandler.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    if(m_loadingComplete && !m_exiting)
    {
	    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	    {
	        Game::Instance()->getStateMachine()->pushState(new PauseState());
	    }
		
		BulletHandler::Instance()->updateBullets();
        
        if(Game::Instance()->getPlayerLives() == 0)
        {
            Game::Instance()->getStateMachine()->changeState(new GameOverState());
        }
		if(pLevel != 0)
        {
            pLevel->update();
        }
	}
}
void PlayState::render()
{
    if(m_loadingComplete)
    {
        if(pLevel != 0)
        {
            pLevel->render();
        }
        
        for(int i = 0; i < Game::Instance()->getPlayerLives(); i++)
        {
            TextureManager::Instance()->drawFrame("lives", i * 30, 0, 32, 30, 0, 0, Game::Instance()->getRenderer(), 0.0, 255);
        }
        
        BulletHandler::Instance()->drawBullets();
    }
}
bool PlayState::onEnter()
{
    Game::Instance()->setPlayerLives(3);
    
    LevelParser levelParser;
    pLevel = levelParser.parseLevel(Game::Instance()->getLevelFiles()[Game::Instance()->getCurrentLevel() - 1].c_str());
    
    TextureManager::Instance()->load("assets/bullet1.png", "bullet1", Game::Instance()->getRenderer());
    TextureManager::Instance()->load("assets/bullet2.png", "bullet2", Game::Instance()->getRenderer());
    TextureManager::Instance()->load("assets/bullet3.png", "bullet3", Game::Instance()->getRenderer());
    TextureManager::Instance()->load("assets/lives.png", "lives", Game::Instance()->getRenderer());
    
    if(pLevel != 0)
    {
        m_loadingComplete = true;
    }

    DEBUG("entering PlayState");
    return true;
}

bool PlayState::onExit()
{
    m_exiting = true;
    
    InputHandler::Instance()->reset();
	BulletHandler::Instance()->clearBullets();

    DEBUG("exiting PlayState");
    return true;
}