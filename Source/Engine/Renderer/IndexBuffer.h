#pragma once
#include "Resources/Resource.h"
#include <SDL3/SDL.h>

namespace STR_FALL
{
	class IndexBuffer : public Resource
	{
	public:
		~IndexBuffer();

		bool Create(uint32_t indexCount, const uint32_t* data, const class Renderer& renderer);
		bool Create(std::vector<uint32_t>& indices, const class Renderer& renderer);
		
		uint32_t GetIndexCount() const { return m_indexCount; }

		friend class Renderer;

        void UpdateGui()
        {
			std::string countString = "Index Count: " + std::to_string(m_indexCount);
			ImGui::Text(countString.c_str());
        }

	private:
		uint32_t m_indexCount = 0;

		SDL_GPUDevice* m_GPUDevice = nullptr;
		SDL_GPUBuffer* m_GPUBuffer = nullptr;
	};
}
