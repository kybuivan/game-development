#ifndef __SDL_GAME_OBJECT_H__
#define __SDL_GAME_OBJECT_H__
#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

    Vector2D& getPosition() { return m_position; }
    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
protected:
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;
    int m_width;
    int m_height;
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    std::string m_textureID;
};

class Player : public SDLGameObject
{
public:
    Player(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
private:
    void handleInput();
};
// Enemy class
class Enemy : public SDLGameObject
{
public:
    Enemy(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
};

// MenuObject class
class MenuObject : public SDLGameObject
{
public:
    MenuObject(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
};

#endif //__SDL_GAME_OBJECT_H__