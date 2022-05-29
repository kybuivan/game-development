#ifndef __TURRET_H__
#define __TURRET_H__

#include <iostream>
#include "GameObjectFactory.h"
#include "BulletHandler.h"
#include "SoundManager.h"
#include <math.h>
#include "Enemy.h"

class Turret : public Enemy
{
public:
    
    Turret()
    {
        m_dyingTime = 1000;
        m_health = 15;
        m_bulletFiringSpeed = 50;
    }
    
    virtual ~Turret() {}

    virtual void collision()
    {
        m_health -= 1;
        
        if(m_health == 0)
        {
            if(!m_bPlayedDeathSound)
            {
                SoundManager::Instance()->playSound("explode", 0);
                
                m_textureID = "largeexplosion";
                m_currentFrame = 0;
                m_numFrames = 9;
                m_width = 60;
                m_height = 60;
                m_bDying = true;
            }
            
        }
    }
    
    virtual void update()
    {
        if(!m_bDying)
        {
            // we want to scroll this object with the rest
            scroll(Game::Instance()->getScrollSpeed());
            
            if(m_bulletCounter == m_bulletFiringSpeed)
            {
                BulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet2", 1, Vector2D(-3, -3));
                BulletHandler::Instance()->addEnemyBullet(m_position.getX() + 20, m_position.getY(), 16, 16, "bullet2", 1, Vector2D(0, -3));
                BulletHandler::Instance()->addEnemyBullet(m_position.getX() + 40, m_position.getY(), 16, 16, "bullet2", 1, Vector2D(3, -3));
                m_bulletCounter = 0;
            }
            
            m_bulletCounter++;
        }
        else
        {
            scroll(Game::Instance()->getScrollSpeed());
            doDyingAnimation();
        }
        
        ShooterObject::update();
    }

};

class TurretCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Turret();
    }
};


#endif //__TURRET_H__
