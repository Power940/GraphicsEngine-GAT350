#include "pch.h"
#include "Text.h"


namespace STR_FALL
{
	Text::~Text() {
		if (m_texture != nullptr) {
			SDL_DestroyTexture(m_texture);
		}
	}

	bool Text::Create(Renderer& renderer, const std::string& text, const Color& color)
	{
		SDL_Color c{ (uint8_t)(color.m_x * 255), (uint8_t)(color.m_y * 255), (uint8_t)(color.m_z * 255), (uint8_t)(color.m_w * 255) };
		SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), text.size(), c);
		if (surface == nullptr) {
			std::cerr << "Could not create surface.\n";
			return false;
		}

		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		if (m_texture == nullptr) {
			SDL_DestroySurface(surface);
			std::cerr << "Could not create texture" << SDL_GetError() << std::endl;
			return false;
		}

		SDL_DestroySurface(surface);

		return true;
	}

	void Text::Draw(Renderer& renderer, float x, float y)
	{
		float width, height;
		bool success = SDL_GetTextureSize(m_texture, &width, &height);
		assert(success);

		SDL_FRect rect{ x, y, width, height };
		success = SDL_RenderTexture(renderer.m_renderer, m_texture, NULL, &rect);
		assert(success);
	}
}