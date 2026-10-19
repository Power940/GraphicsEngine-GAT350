#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>


namespace STR_FALL
{
	class Renderer
	{
	private:
		SDL_Renderer* m_renderer = nullptr;
		SDL_Window* m_window = nullptr;

		SDL_GPUDevice* m_GPUDevice = nullptr;
		SDL_GPUCommandBuffer* m_GPUCommandBuffer = nullptr;
		SDL_GPURenderPass* m_GPURenderPass = nullptr;

		int m_WINDOW_WIDTH = -1;
		int m_WINDOW_HEIGHT = -1;

	public:
        bool Initialize(const char* name, int WINDOW_WIDTH, int WINDOW_HEIGHT);
		void ShutDown();

		SDL_GPUDevice* GetGPUDevice() const { return m_GPUDevice; }
		SDL_Window* GetWindow() const { return m_window; }

		void SetPipeline(const class Pipeline& pipeline);
		void SetVertexBuffer(const class VertexBuffer& vertexBuffer);
		void SetIndexBuffer(const class IndexBuffer& indexBuffer);
		void Draw(uint32_t vertexCount);
		void DrawIndex(const class IndexBuffer& indexBuffer);

		bool BeginFrame();
		bool EndFrame();

		void SetVertexUniforms(uint32_t slot, const void* data, uint32_t size);
		void SetFragmentUniforms(uint32_t slot, const void* data, uint32_t size);

		inline int GetSreenWidth() const { return m_WINDOW_WIDTH; }
		inline int GetSreenHeight() const { return m_WINDOW_HEIGHT; }

		friend struct Text;
		friend class Texture;
		friend class VertexBuffer;
		friend class IndexBuffer;
	};
}