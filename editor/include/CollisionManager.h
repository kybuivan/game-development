#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

#include <vector>

class Player;
class GameObject;
class TileLayer;

class CollisionManager
{
public:
    void checkPlayerEnemyBulletCollision(Player* pPlayer);
    void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);
    void checkEnemyPlayerBulletCollision(const std::vector<GameObject*>& objects);
    void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);
};

#endif //__COLLISION_MANAGER_H__
