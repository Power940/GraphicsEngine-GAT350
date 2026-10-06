#pragma once
#include "Resources/Resource.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <string>


namespace STR_FALL
{
	struct Font : public Resource
	{
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);

	private:
		friend struct Text;

		TTF_Font* m_ttfFont = nullptr;
	};
}