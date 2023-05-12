#ifndef __ANIMATED_GRAPHIC_H__
#define __ANIMATED_GRAPHIC_H__
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public ShooterObject
{
public:
    AnimatedGraphic();
    virtual ~AnimatedGraphic() {}

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
private:
    int m_animateSpeed;
    int m_frameCount;
};

class AnimatedGraphicCreator : public BaseCreator
{
public:
    virtual GameObject* createGameObject() const
    {
        return new AnimatedGraphic();
    }
};

#endif //__ANIMATED_GRAPHIC_H__