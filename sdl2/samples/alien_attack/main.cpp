#include <Game.h>
#include <SoundManager.h>
#include <Player.h>
#include <GameObjectFactory.h>
#include <AnimatedGraphic.h>
#include <ScrollingBackground.h>
#include <MenuButton.h>
#include <MainMenuState.h>
#include "RoofTurret.h"
#include "ShotGlider.h"
#include "Eskeletor.h"
#include "Level1Boss.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
    Uint32 frameStart, frameTime;
    
    if(Game::Instance()->init("Chapter 1", 100, 100, 640, 480, false))
    {
        DEBUG("Game Init");
    }
    else
    {
        return 1;
    }
    std::vector<std::string> levelFiles;
    levelFiles.push_back("assets/maps/map1.tmx");
    levelFiles.push_back("assets/maps/map2.tmx");

    Game::Instance()->setLevelFiles(levelFiles);
    // add some sound effects - TODO move to better place
    SoundManager::Instance()->load("assets/sounds/DST_ElectroRock.ogg", "music1");
    SoundManager::Instance()->load("assets/sounds/boom.wav", "explode");
    SoundManager::Instance()->load("assets/sounds/phaser.wav", "shoot");
    
    SoundManager::Instance()->playSound("music1");

    //InputHandler::Instance()->initialiseJoysticks();

    GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    //GameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
    GameObjectFactory::Instance()->registerType("ScrollingBackground", new ScrollingBackgroundCreator());
    GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    GameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    GameObjectFactory::Instance()->registerType("Turret", new TurretCreator());
    GameObjectFactory::Instance()->registerType("Glider", new GliderCreator());
    GameObjectFactory::Instance()->registerType("ShotGlider", new ShotGliderCreator());
    GameObjectFactory::Instance()->registerType("RoofTurret", new RoofTurretCreator());
    GameObjectFactory::Instance()->registerType("Eskeletor", new EskeletorCreator());
    GameObjectFactory::Instance()->registerType("Level1Boss", new Level1BossCreator());

    Game::Instance()->getStateMachine()->changeState(new MainMenuState());

    while(Game::Instance()->running())
    {
        frameStart = SDL_GetTicks();
        
        Game::Instance()->handleEvents();
        Game::Instance()->update();
        Game::Instance()->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameTime< DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }
    Game::Instance()->clean();
    
    return 0;
}
