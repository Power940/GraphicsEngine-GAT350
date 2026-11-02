#include "pch.h"
#include "MaterialComponent.h"
#include "Core/Factory.h"
#include "LightComponent.h"

namespace STR_FALL
{
	FACTORY_REG(LightComponent)
	
	void STR_FALL::LightComponent::Read(const rapidjson::Value& value)
	{
	}
}