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
}

void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(),
    m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer());
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

    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
    SDLGameObject::update();
}

void Player::handleInput()
{
    if(InputHandler::Instance()->joysticksInitialised())
    {
        if(InputHandler::Instance()->xvalue(0, 1) > 0 || InputHandler::Instance()->xvalue(0, 1) < 0)
        {
            m_velocity.setX(1 * InputHandler::Instance()->xvalue(0, 1));
        }
        if(InputHandler::Instance()->yvalue(0, 1) > 0 || InputHandler::Instance()->yvalue(0, 1) < 0)
        {
            m_velocity.setY(1 * InputHandler::Instance()->yvalue(0, 1));
        }
        if(InputHandler::Instance()->xvalue(0, 2) > 0 || InputHandler::Instance()->xvalue(0, 2) < 0)
        {
            m_velocity.setX(1 * InputHandler::Instance()->xvalue(0, 2));
        }
        if(InputHandler::Instance()->yvalue(0, 2) > 0 || InputHandler::Instance()->yvalue(0, 2) < 0)
        {
            m_velocity.setY(1 * InputHandler::Instance()->yvalue(0, 2));
        }

        if(InputHandler::Instance()->getButtonState(0, 3))
        {
            m_velocity.setX(1);
        }
    }

    if(InputHandler::Instance()->getMouseButtonState(LEFT))
    {
        m_velocity.setX(1);
    }

    //Vector2D* vec = InputHandler::Instance()->getMousePosition();
    //m_velocity = (*vec - m_position) / 100;

    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        m_velocity.setX(2);
    }

    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
    {
        m_velocity.setX(-2);
    }

    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
    {
        m_velocity.setY(-2);
    }
    
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
    {
        m_velocity.setY(2);
    }
}

void Player::clean()
{
}

Enemy::Enemy(const LoaderParams* pParams) :
    SDLGameObject(pParams)
{
}

void Enemy::draw()
{
    SDLGameObject::draw(); // we now use SDLGameObject
}

void Enemy::update()
{
    m_position.setX(m_position.getX() + 1);
    m_position.setY(m_position.getY() + 1);
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Enemy::clean()
{
}