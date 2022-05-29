#ifndef __ROFF_TURRET_H__
#define __ROFF_TURRET_H__

#include "Turret.h"

class RoofTurret : public Turret
{
public:
    
    virtual ~RoofTurret() {}
    
    virtual void draw()
    {
        TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
                                              m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer(), m_angle, m_alpha, SDL_FLIP_VERTICAL);
    }
    
    virtual void update()
    {
        if(!m_bDying)
        {
            // we want to scroll this object with the rest
            scroll(Game::Instance()->getScrollSpeed());
            
            if(m_bulletCounter == m_bulletFiringSpeed)
            {
                BulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(-3, 3));
                BulletHandler::Instance()->addEnemyBullet(m_position.getX() + 20, m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(0, 3));
                BulletHandler::Instance()->addEnemyBullet(m_position.getX() + 40, m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(3, 3));
                m_bulletCounter = 0;
            }
            
            m_bulletCounter++;
        }
        else
        {
            scroll(Game::Instance()->getScrollSpeed());
            doDyingAnimation();
        }
    }
};

class RoofTurretCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new RoofTurret();
    }
};

#endif //__ROFF_TURRET_H__
