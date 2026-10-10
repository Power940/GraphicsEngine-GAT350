#pragma once
#include "Resources/Resource.h"
#include <SDL3/SDL.h>
#include <string>

namespace STR_FALL
{
	class Shader : public Resource
	{
	public:
		virtual ~Shader();

		bool Load(const std::string& filename, class Renderer& renderer);

		friend class Pipeline;

	private:
		SDL_GPUShader* m_GPUShader = nullptr;
		SDL_GPUDevice* m_GPUDevice = nullptr;
	};
}
