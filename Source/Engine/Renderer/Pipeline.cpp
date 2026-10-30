#include "pch.h"
#include "Pipeline.h"
#include "Shader.h"

namespace STR_FALL
{
	Pipeline::~Pipeline()
	{
		if (m_GPUDevice && m_GPUPipeline) { SDL_ReleaseGPUGraphicsPipeline(m_GPUDevice, m_GPUPipeline); }
	}

	bool Pipeline::Create(const Shader& vertexShader, const Shader& fragmentShader, SDL_GPUDevice* gpuDevice, SDL_Window* window)
	{
		m_GPUDevice = gpuDevice;

		std::array colorTargetDescriptions{
			SDL_GPUColorTargetDescription{
				.format = SDL_GetGPUSwapchainTextureFormat(m_GPUDevice, window)
			}
		};
		
		SDL_GPUGraphicsPipelineCreateInfo pipelineCreateInfo{
			.vertex_shader = vertexShader.m_GPUShader,
			.fragment_shader = fragmentShader.m_GPUShader,
			.vertex_input_state = SDL_GPUVertexInputState{
				.vertex_buffer_descriptions = m_vertexBufferDescriptions.data(),
				.num_vertex_buffers = static_cast<uint32_t>(m_vertexBufferDescriptions.size()),
				.vertex_attributes = m_vertexAttributes.data(),
				.num_vertex_attributes = static_cast<uint32_t>(m_vertexAttributes.size())
			},
			.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
			.rasterizer_state = SDL_GPURasterizerState{
				.fill_mode = SDL_GPU_FILLMODE_FILL,
				.cull_mode = SDL_GPU_CULLMODE_BACK,
				.front_face = SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE
			},
			.depth_stencil_state = SDL_GPUDepthStencilState{
				.compare_op = SDL_GPU_COMPAREOP_LESS,
				.enable_depth_test = true,
				.enable_depth_write = true
			},
			.target_info = SDL_GPUGraphicsPipelineTargetInfo{
				.color_target_descriptions = colorTargetDescriptions.data(),
				.num_color_targets = static_cast<uint32_t>(colorTargetDescriptions.size()),
				.depth_stencil_format = SDL_GPU_TEXTUREFORMAT_D32_FLOAT,
				.has_depth_stencil_target = true
			}
		};

		m_GPUPipeline = SDL_CreateGPUGraphicsPipeline(m_GPUDevice, &pipelineCreateInfo);
		if (!m_GPUPipeline) { std::cerr << "ERROR: Pipeline::Create SDL_CreateGPUGraphicsPipeline failed: " << SDL_GetError() << std::endl; }

		return true;
	}

	void Pipeline::AddVertexBuffer(uint32_t pitch)
	{
		SDL_GPUVertexBufferDescription description{
			.slot = static_cast<uint32_t>(m_vertexBufferDescriptions.size()),
			.pitch = pitch,
			.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
			.instance_step_rate = 0
		};

		m_vertexBufferDescriptions.push_back(description);
	}

	void Pipeline::AddVertexAttribute(uint32_t location, SDL_GPUVertexElementFormat format, uint32_t offset)
	{
		SDL_GPUVertexAttribute attribute{
			.location = location,
			.buffer_slot = 0,
			.format = format,
			.offset = offset
		};

		m_vertexAttributes.push_back(attribute);
	}
}