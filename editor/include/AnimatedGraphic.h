#ifndef __ANIMATED_GRAPHIC_H__
#define __ANIMATED_GRAPHIC_H__
#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic(const LoaderParams* pParams, int animSpeed);

	void update();
	void draw();
	void clean();
private:
	int m_animSpeed;
};

#endif //__ANIMATED_GRAPHIC_H__