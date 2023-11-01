#ifndef __MENU_BUTTON_H__
#define __MENU_BUTTON_H__
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class MenuButton : public ShooterObject
{
public:
    MenuButton();
    
    virtual ~MenuButton() {}
    
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    
    virtual void draw();
    virtual void update();
    virtual void clean();

    void setCallback(void(*callback)()) { m_callback = callback;}
    int getCallbackID() { return m_callbackID; }
private:
    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    void (*m_callback)();
    int m_callbackID;
    bool m_bReleased;
};

class MenuButtonCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new MenuButton();
    }
};
#endif //__MENU_BUTTON_H__