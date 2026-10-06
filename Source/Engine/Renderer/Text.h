#pragma once
#include <Math/Structs.h>
#include "Font.h"
#include "Renderer.h"
#include <Resources/Resource.h>
#include <SDL3/SDL_render.h>
#include <string>


namespace STR_FALL
{
	struct Text
	{
	public:
		Text() = default;
		Text(res_t<Font> font) : m_font(font) {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, float x, float y);

	private:
		res_t<Font> m_font = nullptr;
		SDL_Texture* m_texture = nullptr;
	};
}