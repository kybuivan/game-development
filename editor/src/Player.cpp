#include "Player.h"
#include "InputHandler.h"

Player::Player() : SDLGameObject() {}

void Player::draw()
{
	SDLGameObject::draw();
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

void Player::load(const LoaderParams *pParams)
{
	SDLGameObject::load(pParams);
}