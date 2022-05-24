#include "AnimatedGraphic.h"

//constructor for AnimatedGraphic class
AnimatedGraphic::AnimatedGraphic() : SDLGameObject()
{
}

void AnimatedGraphic::draw()
{
	SDLGameObject::draw();
}

//update function of animated graphic class
void AnimatedGraphic::update()
{
	
	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animateSpeed)) % m_numFrames));
}

void AnimatedGraphic::clean()
{
	SDLGameObject::clean();
}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_animateSpeed = pParams->getAnimateSpeed();
}