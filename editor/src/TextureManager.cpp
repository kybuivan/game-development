#include "TextureManager.h"
#include "logging.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

TextureManager* TextureManager::s_pInstance = 0;

TextureManager::~TextureManager()
{
}

bool TextureManager::load(std::string fileName, std::string
id, SDL_Renderer* pRenderer)
{
    int w, h, comp;
    int req_format = STBI_rgb_alpha;
    unsigned char* data = stbi_load(fileName.c_str(), &w, &h, &comp, req_format);
    
    int depth, pitch;
    Uint32 pixel_format;
    if (req_format == STBI_rgb) {
        depth = 24;
        pitch = 3*w; // 3 bytes per pixel * pixels per row
        pixel_format = SDL_PIXELFORMAT_RGB24;
    } else { // STBI_rgb_alpha (RGBA)
        depth = 32;
        pitch = 4*w;
        pixel_format = SDL_PIXELFORMAT_RGBA32;
    }

    SDL_Surface* pTempSurface = SDL_CreateRGBSurfaceWithFormatFrom((void*)data, w, h,
                                                       depth, pitch, pixel_format);
    if (pTempSurface == 0) {
        stbi_image_free(data);
        ERROR("Creating surface failed: %s", SDL_GetError());
        return false; // SDL init fail
    }

    SDL_Texture* pTexture =
    SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    // .. *and* the data used by the surface!
    stbi_image_free(data);
    
    // everything went ok, add the texture to our list
    if(pTexture != 0)
    {
        m_textureMap[id] = pTexture;
        return true;
    }
    // reaching here means something went wrong
    return false;
}

void TextureManager::draw(std::string id, int x, int y, int
width, int height, SDL_Renderer* pRenderer,
SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
    &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int
width, int height, int currentRow, int currentFrame, SDL_Renderer
*pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
    &destRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id)
{
    m_textureMap.erase(id);
}