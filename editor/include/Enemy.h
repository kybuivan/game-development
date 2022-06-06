#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "PlatformerObject.h"

// Enemy base class
class Enemy : public PlatformerObject
{
public:
    
    virtual std::string type() { return "Enemy"; }
    
protected:
    
    int m_health;
    
    Enemy() : PlatformerObject() {}
    virtual ~Enemy() {}
};

#endif //__ENEMY_H__