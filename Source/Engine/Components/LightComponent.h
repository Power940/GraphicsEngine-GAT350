#pragma once
#include "Component.h"

namespace STR_FALL
{
	class LightComponent : public Component
	{
	public:
		CLASS_PROTOTYPE(LightComponent)

		void Read(const rapidjson::Value& value) override;
		 
	private:
	};
}