#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__
#include "SDL.h"
#include "SDL_joystick.h"
#include "Vector2D.h"
#include <vector>

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    const int m_joystickDeadZone = 10000;

    static InputHandler* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new InputHandler();
            return s_pInstance;
        }
        return s_pInstance;
    }
    void update();
    void clean();
    void initialiseJoysticks();
    bool joysticksInitialised() { return m_bJoysticksInitialised; }
    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);
    bool getButtonState(int joy, int buttonNumber)
    {
        return m_buttonStates[joy][buttonNumber];
    }

    bool getMouseButtonState(int buttonNumber)
    {
        return m_mouseButtonStates[buttonNumber];
    }

    Vector2D* getMousePosition()
    {
        return m_mousePosition;
    }

    bool isKeyDown(SDL_Scancode key);
private:
    InputHandler(){}
    ~InputHandler() {}
    // private functions to handle different event types
    // handle keyboard events
    void onKeyDown();
    void onKeyUp();
    // handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);
    // handle joysticks events
    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);
private:
    static InputHandler* s_pInstance;
    const Uint8* m_keystates;
    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<std::vector<bool>> m_buttonStates;
    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;
    bool m_bJoysticksInitialised;
};

#endif //__INPUT_HANDLER_H__