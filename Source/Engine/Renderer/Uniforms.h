#pragma once
#include <glm/glm.hpp>
#include <cstdint>

#define CHECK_UNIFORM_BOUNDARY(T) static_assert((sizeof(T) % 16) == 0)

namespace STR_FALL
{
	enum class UniformSlot : uint32_t
	{
		Object = 0,
		Frame = 1,
		Light = 2,
		Material = 3
	};

	struct ObjectUniform
	{
		glm::mat4 model;
		glm::mat4 normalMatrix;
	};
	CHECK_UNIFORM_BOUNDARY(ObjectUniform);

	struct FrameUniform
	{
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 viewProjection;
		glm::vec3 cameraPosition;
		float time;
	};
	CHECK_UNIFORM_BOUNDARY(FrameUniform);
}
