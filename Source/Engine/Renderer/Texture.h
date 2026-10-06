#pragma once
#include <Math/Structs.h>
#include <Resources/Resource.h>
#include <SDL3/SDL_render.h>
#include <string>


namespace STR_FALL
{
	class Texture : public Resource
	{
	friend class Renderer;

	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, Renderer& renderer);

		SDL_Texture* m_texture = nullptr;
		Vector2 m_size = Vector2();
	};
}