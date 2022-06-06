#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

#include <vector>
#include "Player.h"
#include "GameObject.h"

class CollisionManager
{
public:
    void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);
};

#endif //__COLLISION_MANAGER_H__
