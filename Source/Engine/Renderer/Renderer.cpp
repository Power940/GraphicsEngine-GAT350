#include "pch.h"
#include "Renderer.h"
#include "Renderer/Pipeline.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Texture.h"


namespace STR_FALL
{
    bool Renderer::Initialize(const char* name, int WINDOW_WIDTH, int WINDOW_HEIGHT)
    {
        SDL_Init(SDL_INIT_VIDEO);

        m_window = SDL_CreateWindow(name, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        if (m_window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        SDL_GPUShaderFormat formats = SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL;
        m_GPUDevice = SDL_CreateGPUDevice(formats, true, nullptr);
        if (!m_GPUDevice)
        {
            std::cerr << "Failed to create GPU Device: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        SDL_ClaimWindowForGPUDevice(m_GPUDevice, m_window);
        std::cout << "GPU Driver Initialized: " << SDL_GetGPUDeviceDriver(m_GPUDevice) << std::endl;

        m_WINDOW_WIDTH = WINDOW_WIDTH;
        m_WINDOW_HEIGHT = WINDOW_HEIGHT;

        return true;
    }
    void Renderer::ShutDown()
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void Renderer::SetPipeline(const Pipeline& pipeline) { SDL_BindGPUGraphicsPipeline(m_GPURenderPass, pipeline.m_GPUPipeline); }
    void Renderer::SetVertexBuffer(const VertexBuffer& vertexBuffer)
    {
        SDL_GPUBufferBinding binding{
            .buffer = vertexBuffer.m_GPUBuffer,
            .offset = 0
        };
        SDL_BindGPUVertexBuffers(m_GPURenderPass, 0, &binding, 1);
    }
    void Renderer::SetIndexBuffer(const IndexBuffer& indexBuffer)
    {
        SDL_GPUBufferBinding binding{
            .buffer = indexBuffer.m_GPUBuffer,
            .offset = 0
        };
        SDL_BindGPUIndexBuffer(m_GPURenderPass, &binding, SDL_GPU_INDEXELEMENTSIZE_32BIT);
    }
    void Renderer::Draw(uint32_t vertexCount) { SDL_DrawGPUPrimitives(m_GPURenderPass, vertexCount, 1, 0, 0); }
    void Renderer::DrawIndex(const IndexBuffer& indexBuffer)
    {
        SDL_DrawGPUIndexedPrimitives(m_GPURenderPass, indexBuffer.GetIndexCount(), 1, 0, 0, 0);
    }

    bool Renderer::BeginFrame()
    {
        m_GPUCommandBuffer = SDL_AcquireGPUCommandBuffer(m_GPUDevice);
        if (!m_GPUCommandBuffer)
        {
            std::cerr << "Could not acquire command buffer: " << SDL_GetError() << std::endl;
            return false;
        }


        SDL_GPUTexture* swapchainTexture = nullptr;
        if (!SDL_WaitAndAcquireGPUSwapchainTexture(m_GPUCommandBuffer, m_window, &swapchainTexture, nullptr, nullptr))
        {
            std::cerr << "Could not acquire swapchain texture: " << SDL_GetError() << std::endl;
            return false;
        }

        if (swapchainTexture != nullptr)
        {
            // configure the color target attachments (This handles clearing the screen)
            SDL_GPUColorTargetInfo color_target_info{};
            color_target_info.texture = swapchainTexture;
            color_target_info.clear_color = SDL_FColor{ 0.3f, 0.3f, 0.3f, 1.0f };
            color_target_info.load_op = SDL_GPU_LOADOP_CLEAR;
            color_target_info.store_op = SDL_GPU_STOREOP_STORE;

            m_GPURenderPass = SDL_BeginGPURenderPass(m_GPUCommandBuffer, &color_target_info, 1, nullptr);
        }

        return true;
    }
    bool Renderer::EndFrame()
    {
        if (m_GPURenderPass)
        {
            SDL_EndGPURenderPass(m_GPURenderPass);
            m_GPURenderPass = nullptr;
        }

        if (!SDL_SubmitGPUCommandBuffer(m_GPUCommandBuffer))
        {
            std::cerr << "Could not submit command buffer: " << SDL_GetError() << std::endl;
            return false;
        }

        m_GPUCommandBuffer = nullptr;

        return true;
    }

    void Renderer::SetVertexUniforms(uint32_t slot, const void* data, uint32_t size)
    {
        SDL_PushGPUVertexUniformData(m_GPUCommandBuffer, slot, data, size);
    }
    void Renderer::SetFragmentUniforms(uint32_t slot, const void* data, uint32_t size)
    {
        SDL_PushGPUFragmentUniformData(m_GPUCommandBuffer, slot, data, size);
    }

    void Renderer::SetFragmentTexture(uint32_t slot, const Texture& texture)
    {
        SDL_GPUTextureSamplerBinding binding
        {
            .texture = texture.m_GPUTexture,
            .sampler = texture.m_GPUSampler
        };

        SDL_BindGPUFragmentSamplers(m_GPURenderPass, slot, &binding, 1);
    }
}