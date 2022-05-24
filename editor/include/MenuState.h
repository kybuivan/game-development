#ifndef __MENU_STATE_H__
#define __MENU_STATE_H__
#include"GameState.h"

class MenuState : public GameState
{
protected:
    typedef void(*Callback)();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
    std::vector<Callback> m_callbacks;
};
#endif //__MENU_STATE_H__