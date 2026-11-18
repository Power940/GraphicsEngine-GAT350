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

		bool Load(const std::string& filename, const class Renderer& renderer);

		friend class Pipeline;

		void UpdateGui()
		{
			std::string nameString = "Name: " + m_name;
			ImGui::Text(nameString.c_str());
		}

	private:
		SDL_GPUShader* m_GPUShader = nullptr;
		SDL_GPUDevice* m_GPUDevice = nullptr;
	};
}
