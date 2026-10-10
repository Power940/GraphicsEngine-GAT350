#include "pch.h"
#include "VertexBuffer.h"

namespace STR_FALL
{
	VertexBuffer::~VertexBuffer()
	{
		if (m_GPUBuffer && m_GPUDevice) { SDL_ReleaseGPUBuffer(m_GPUDevice, m_GPUBuffer); }
	}

	bool VertexBuffer::Create(uint32_t vertexCount, uint32_t vertexSize, const uint8_t* data, SDL_GPUDevice* gpuDevice)
	{
		m_vertexCount = vertexCount;
		m_GPUDevice = gpuDevice;

		uint32_t verticesSize = m_vertexCount * vertexSize;
		SDL_GPUBufferCreateInfo vertexBufferCreateInfo{
			.usage = SDL_GPU_BUFFERUSAGE_VERTEX,
			.size = verticesSize
		};
		m_GPUBuffer = SDL_CreateGPUBuffer(m_GPUDevice, &vertexBufferCreateInfo);
		if (!m_GPUBuffer) { std::cerr << "Could not create vertex buffer: " << SDL_GetError() << std::endl; return false; }

		SDL_GPUTransferBufferCreateInfo transferBufferCreateInfo{
			.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			.size = verticesSize
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
			SDL_ReleaseGPUTransferBuffer(gpuDevice, transferBuffer);
			SDL_ReleaseGPUBuffer(gpuDevice, m_GPUBuffer);
			m_GPUBuffer = nullptr;
			return false;
		}
		memcpy(transferData, data, verticesSize);
		SDL_UnmapGPUTransferBuffer(m_GPUDevice, transferBuffer);

		SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(m_GPUDevice);
		if (!commandBuffer)
		{
			std::cerr << "Could not acquire GPU command buffer: " << SDL_GetError() << std::endl;
			SDL_ReleaseGPUTransferBuffer(gpuDevice, transferBuffer);
			SDL_ReleaseGPUBuffer(gpuDevice, m_GPUBuffer);
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
			.size = verticesSize
		};

		SDL_UploadToGPUBuffer(copyPass, &bufferLocation, &bufferRegion, false);
		SDL_EndGPUCopyPass(copyPass);
		if (!SDL_SubmitGPUCommandBuffer(commandBuffer))
		{
			std::cerr << "Could not submit GPU command buffer: " << SDL_GetError() << std::endl;
			SDL_ReleaseGPUTransferBuffer(gpuDevice, transferBuffer);
			SDL_ReleaseGPUBuffer(gpuDevice, m_GPUBuffer);
			m_GPUBuffer = nullptr;
			return false;
		}

		SDL_ReleaseGPUTransferBuffer(m_GPUDevice, transferBuffer);

		return true;
	}
}