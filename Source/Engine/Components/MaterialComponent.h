#pragma once
#include "Component.h"

namespace STR_FALL
{
	class MaterialComponent : public Component
	{
	public:
		CLASS_PROTOTYPE(MaterialComponent)

		void Read(const rapidjson::Value& value) override;

	private:
	};
}