#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include "Uniforms.h"


namespace STR_FALL
{
	class Renderer
	{
	private:
		SDL_Window* m_window = nullptr;
		SDL_GPUDevice* m_GPUDevice = nullptr;
		SDL_GPUCommandBuffer* m_GPUCommandBuffer = nullptr;
		SDL_GPURenderPass* m_GPURenderPass = nullptr;
		SDL_GPUTexture* m_GPUDepthTexture = nullptr;
		SDL_GPUTexture* m_GPUSwapchainTexture = nullptr;

		int m_WINDOW_WIDTH = -1;
		int m_WINDOW_HEIGHT = -1;
		float m_ASPECT = -1.0f;

	public:
        bool Initialize(const char* name, int WINDOW_WIDTH, int WINDOW_HEIGHT);
		void ShutDown();

		inline SDL_GPUDevice* GetGPUDevice() const { return m_GPUDevice; }
		inline SDL_Window* GetWindow() const { return m_window; }
		inline int GetSreenWidth() const { return m_WINDOW_WIDTH; }
		inline int GetSreenHeight() const { return m_WINDOW_HEIGHT; }
		inline float GetAspect() const { return m_ASPECT; }
		inline SDL_GPUCommandBuffer* GetGPUCommandBuffer() const { return m_GPUCommandBuffer; }
		inline SDL_GPUTexture* GetGPUSwapchainTexture() const { return m_GPUSwapchainTexture; }

		void SetPipeline(const class Pipeline& pipeline) const;
		void SetVertexBuffer(const class VertexBuffer& vertexBuffer) const;
		void SetIndexBuffer(const class IndexBuffer& indexBuffer) const;

		void SetVertexUniforms(UniformSlot slot, const void* data, uint32_t size) const;
		void SetFragmentUniforms(UniformSlot slot, const void* data, uint32_t size) const;
		void SetFragmentTexture(uint32_t slot, const class Texture& texture) const;
		void SetMaterial(const class MaterialInstance& instance) const;

		void Draw(uint32_t vertexCount);
		void DrawIndex(const class IndexBuffer& indexBuffer);

		bool BeginFrame();
		bool EndFrame();
		void EndRenderPass();

		void CreateDepthBuffer();

		friend struct Text;
		friend class Texture;
		friend class VertexBuffer;
		friend class IndexBuffer;
	};
}