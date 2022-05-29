#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "ShooterObject.h"

// Enemy base class
class Enemy : public ShooterObject
{
public:
    
    virtual std::string type() { return "Enemy"; }
    
protected:
    
    int m_health;
    
    Enemy() : ShooterObject() {}
    virtual ~Enemy() {}
};

#endif //__ENEMY_H__