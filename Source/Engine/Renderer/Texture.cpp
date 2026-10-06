#include "pch.h"
#include "Texture.h"


namespace STR_FALL
{
    Texture::~Texture()
    {
        if (m_texture) { SDL_DestroyTexture(m_texture); }
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer)
    {
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            std::cerr << "Could not load image: " << filename << std::endl;
            return false;
        }

        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
        SDL_DestroySurface(surface);
        if (!m_texture)
        {
            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }

        if (!SDL_GetTextureSize(m_texture, &(m_size.m_x), &(m_size.m_y)))
        {
            std::cerr << "Could not set texture size: " << filename << std::endl;
            return false;
        }

        return true;
    }
}