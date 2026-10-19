#include "pch.h"
#include "IndexBuffer.h"
#include "Renderer.h"

namespace STR_FALL
{
	IndexBuffer::~IndexBuffer()
	{
		if (m_GPUBuffer && m_GPUDevice) { SDL_ReleaseGPUBuffer(m_GPUDevice, m_GPUBuffer); }
	}

	bool IndexBuffer::Create(uint32_t indexCount, const uint32_t* data, const Renderer& renderer)
	{
		m_indexCount = indexCount;
		m_GPUDevice = renderer.m_GPUDevice;

		uint32_t indicesSize = m_indexCount * sizeof(uint32_t);
		SDL_GPUBufferCreateInfo indexBufferCreateInfo{
			.usage = SDL_GPU_BUFFERUSAGE_INDEX,
			.size = indicesSize
		};
		m_GPUBuffer = SDL_CreateGPUBuffer(m_GPUDevice, &indexBufferCreateInfo);
		if (!m_GPUBuffer) { std::cerr << "Could not create index buffer: " << SDL_GetError() << std::endl; return false; }

		SDL_GPUTransferBufferCreateInfo transferBufferCreateInfo{
			.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			.size = indicesSize
		};
		SDL_GPUTransferBuffer* transferBuffer = SDL_CreateGPUTransferBuffer(m_GPUDevice, &transferBufferCreateInfo);
		if (!transferBuffer)
		{
			std::cerr << "Could not create transfer buffer: " << SDL_GetError() << std::endl;
			SDL_ReleaseGPUBuffer(m_GPUDevice, m_GPUBuffer);
			m_GPUBuffer = nullptr;
			return false;
		}

		uint8_t* transferData = static_cast<uint8_t*>(SDL_MapGPUTransferBuffer(m_GPUDevice, transferBuffer, false));
		if (!transferData)
		{
			std::cerr << "Could not map transfer buffer: " << SDL_GetError() << std::endl;
			SDL_ReleaseGPUTransferBuffer(m_GPUDevice, transferBuffer);
			SDL_ReleaseGPUBuffer(m_GPUDevice, m_GPUBuffer);
			m_GPUBuffer = nullptr;
			return false;
		}
		memcpy(transferData, data, indicesSize);
		SDL_UnmapGPUTransferBuffer(m_GPUDevice, transferBuffer);

		SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(m_GPUDevice);
		if (!commandBuffer)
		{
			std::cerr << "Could not acquire GPU command buffer: " << SDL_GetError() << std::endl;
			SDL_ReleaseGPUTransferBuffer(m_GPUDevice, transferBuffer);
			SDL_ReleaseGPUBuffer(m_GPUDevice, m_GPUBuffer);
			m_GPUBuffer = nullptr;
			return false;
		}
		SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(commandBuffer);
		SDL_GPUTransferBufferLocation bufferLocation{
			.transfer_buffer = transferBuffer,
			.offset = 0
		};
		SDL_GPUBufferRegion bufferRegion{
			.buffer = m_GPUBuffer,
			.offset = 0,
			.size = indicesSize
		};

		SDL_UploadToGPUBuffer(copyPass, &bufferLocation, &bufferRegion, false);
		SDL_EndGPUCopyPass(copyPass);
		if (!SDL_SubmitGPUCommandBuffer(commandBuffer))
		{
			std::cerr << "Could not submit GPU command buffer: " << SDL_GetError() << std::endl;
			SDL_ReleaseGPUTransferBuffer(m_GPUDevice, transferBuffer);
			SDL_ReleaseGPUBuffer(m_GPUDevice, m_GPUBuffer);
			m_GPUBuffer = nullptr;
			return false;
		}

		SDL_ReleaseGPUTransferBuffer(m_GPUDevice, transferBuffer);

		return true;
	}


	bool IndexBuffer::Create(std::vector<uint32_t>& indices, const Renderer& renderer)
	{
		return Create(static_cast<uint32_t>(indices.size()), indices.data(), renderer);
	}
}