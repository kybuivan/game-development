#ifndef __LOADER_PARAMS_H__
#define __LOADER_PARAMS_H__
#include <string>

class LoaderParams
{
public:
    LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animateSpeed = 0) :
        m_x(x),
        m_y(y),
        m_width(width),
        m_height(height),
        m_textureID(textureID),
        m_numFrames(numFrames),
        m_callbackID(callbackID),
        m_animateSpeed(animateSpeed)
    { }
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getNumFrames() const { return m_numFrames; }
    int getCallbackID() const { return  m_callbackID; }
    int getAnimateSpeed() const { return m_animateSpeed; }
    std::string getTextureID() const { return m_textureID; }
private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_numFrames;
    int m_callbackID;
    int m_animateSpeed;
    std::string m_textureID;
};

#endif //__LOADER_PARAMS_H__