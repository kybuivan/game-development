#include "Enemy.h"

Enemy::Enemy() : SDLGameObject() 
{
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::load(const LoaderParams *params) {
    SDLGameObject::load(params);

    m_velocity.setY(2);
}

void Enemy::clean() {}

void Enemy::update() {
    m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));
    if(m_position.getY() < 0)
    {
        m_velocity.setY(2);
    }
    else if(m_position.getY() > 400)
    {
        m_velocity.setY(-2);
    }
    SDLGameObject::update();
}