#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton() : PlatformerObject(), m_callback(0), m_bReleased(true)
{
}

void MenuButton::draw()
{
    PlatformerObject::draw(); // use the base class drawing
}

void MenuButton::update()
{
    Vector2D* pMousePos = InputHandler::Instance()->getMousePosition();
    if(pMousePos->getX() < (m_position.getX() + m_width)
        && pMousePos->getX() > m_position.getX()
        && pMousePos->getY() < (m_position.getY() + m_height)
        && pMousePos->getY() > m_position.getY())
    {
        m_currentFrame = MOUSE_OVER;
        if(InputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
        {
            m_currentFrame = CLICKED;
            
            if(m_callback != 0)
            {
            	m_callback(); // call our callback function
            }
            
            m_bReleased = false;
        }
        else if(!InputHandler::Instance()->getMouseButtonState(LEFT))
        {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    }
    else
    {
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::load(std::unique_ptr<LoaderParams> const &pParams)
{
    PlatformerObject::load(std::move(pParams));
    m_callbackID = pParams->getCallbackID();
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::clean()
{
    PlatformerObject::clean();
}