#include "AnimatedGraphic.h"

//constructor for AnimatedGraphic class
AnimatedGraphic::AnimatedGraphic() : PlatformerObject()
{
}

void AnimatedGraphic::draw()
{
	PlatformerObject::draw();
}

//update function of animated graphic class
void AnimatedGraphic::update()
{
	
	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animateSpeed)) % m_numFrames));
}

void AnimatedGraphic::clean()
{
	PlatformerObject::clean();
}

void AnimatedGraphic::load(std::unique_ptr<LoaderParams> const &pParams)
{
	PlatformerObject::load(pParams);
	m_animateSpeed = pParams->getAnimateSpeed();
}