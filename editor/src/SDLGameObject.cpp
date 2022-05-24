#include "SDLGameObject.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) :
    GameObject(pParams)
    , m_position(pParams->getX(), pParams->getY())
    , m_velocity(0,0)
    , m_acceleration(0,0)
{
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();

    m_currentRow = 1;
    m_currentFrame = 1;

    m_numFrames = 6;
}

void SDLGameObject::draw()
{
    if(m_velocity.getX() > 0)
    {
        TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
            m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
    }
    else
    {
        TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
            m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer());
    }
}

void SDLGameObject::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}
void SDLGameObject::clean()
{
}

Player::Player(const LoaderParams* pParams) :
SDLGameObject(pParams)
{
}

void Player::draw()
{
    SDLGameObject::draw(); // we now use SDLGameObject
}

void Player::update()
{
    m_velocity.setX(0);
    m_velocity.setY(0);
    handleInput(); // add our function

    m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));
    SDLGameObject::update();
}

void Player::handleInput()
{
    Vector2D* target = InputHandler::Instance()->getMousePosition();
    m_velocity = *target - m_position;
    m_velocity /= 50;
}

void Player::clean()
{
}

Enemy::Enemy(const LoaderParams* pParams) :
    SDLGameObject(pParams)
{
    m_velocity.setY(2);
    m_velocity.setX(0.001);
}

void Enemy::draw()
{
    SDLGameObject::draw(); // we now use SDLGameObject
}

void Enemy::update()
{
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

void Enemy::clean()
{
}

MenuObject::MenuObject(const LoaderParams* pParams) :
    SDLGameObject(pParams)
{
}

void MenuObject::draw()
{
    SDLGameObject::draw(); // we now use SDLGameObject
}

void MenuObject::update()
{
    m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));
}

void MenuObject::clean()
{
}