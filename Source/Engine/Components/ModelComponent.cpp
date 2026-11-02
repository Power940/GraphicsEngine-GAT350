#include "pch.h"
#include "ModelComponent.h"
#include "Core/Factory.h"

namespace STR_FALL
{
	FACTORY_REG(ModelComponent)

	void ModelComponent::Draw(class Renderer& r)
	{
	}
	void ModelComponent::Read(const rapidjson::Value& value)
	{
	}
}