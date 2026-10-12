#include "pch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Core/file.h"

namespace STR_FALL
{
	Shader::~Shader()
	{
		if (m_GPUDevice && m_GPUShader) { SDL_ReleaseGPUShader(m_GPUDevice, m_GPUShader); }
	}

	bool Shader::Load(const std::string& filename, Renderer& renderer, uint32_t uniformCount)
	{
		m_GPUDevice = renderer.GetGPUDevice();

		SDL_GPUShaderStage stage;
		if (filename.find(".vert") != std::string::npos) { stage = SDL_GPU_SHADERSTAGE_VERTEX; }
		else if (filename.find(".frag") != std::string::npos) { stage = SDL_GPU_SHADERSTAGE_FRAGMENT; }
		else { std::cerr << "ERROR: Shader::Load file isn't .vert or .frag" << std::endl; return false; }

		SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;
		std::string shaderFilename = filename;

		const char* entrypoint = "main";

		SDL_GPUShaderFormat backendFormats = SDL_GetGPUShaderFormats(m_GPUDevice);
		if (backendFormats & SDL_GPU_SHADERFORMAT_SPIRV) { shaderFilename += ".spv"; format = SDL_GPU_SHADERFORMAT_SPIRV; }
		else if (backendFormats & SDL_GPU_SHADERFORMAT_DXIL) { shaderFilename += ".dxil"; format = SDL_GPU_SHADERFORMAT_DXIL; }
		else { std::cerr << "ERROR: Shader::Load no supported shader formmat" << std::endl; return false; }

		std::vector<uint8_t> bytes = ReadBinaryFile(shaderFilename);
		if (bytes.empty()) { std::cerr << "ERROR: Shader::Load could not ReadBinaryFile on file: " << shaderFilename << std::endl; return false; }

		SDL_GPUShaderCreateInfo shaderInfo{
			.code_size = bytes.size(),
			.code = bytes.data(),
			.entrypoint = entrypoint,
			.format = format,
			.stage = stage,
			.num_uniform_buffers = uniformCount
		};

		m_GPUShader = SDL_CreateGPUShader(m_GPUDevice, &shaderInfo);

		if (!m_GPUShader) { std::cerr << "ERROR: Shader::Load SDL_CreateGPUShader failed" << std::endl; return false; }

		return true;
	}
}