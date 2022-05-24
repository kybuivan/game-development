#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "GameObjectFactory.h"
#include "SDLGameObject.h"

class Enemy : public SDLGameObject {
public:
    Enemy();

	void draw();
	void update();
	void clean();
    virtual void load(const LoaderParams* params);
};

class EnemyCreator : public BaseCreator {
public:
    GameObject* createGameObject() const {
        return new Enemy();
    }
};

#endif //__ENEMY_H__