#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__
#include <string>
#include <map>
#include<SDL.h>

class TextureManager
{
public:
    ~TextureManager();

    static TextureManager* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new TextureManager();
            return s_pInstance;
        }
        return s_pInstance;
    }

    bool load(std::string fileName,std::string id, SDL_Renderer* pRenderer);
    // draw
    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // drawframe
    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // drawTile
    void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);

    // clearTextureMap
    void clearFromTextureMap(std::string id);
private:
    /* data */
    TextureManager(/* args */){}

    std::map<std::string, SDL_Texture*> m_textureMap;
    static TextureManager* s_pInstance;
};

#endif //__TEXTURE_MANAGER_H__