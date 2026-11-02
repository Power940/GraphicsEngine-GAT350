#pragma once
#include "RendererComponent.h"

namespace STR_FALL
{
	class ModelComponent : public RendererComponent
	{
	public:
		CLASS_PROTOTYPE(ModelComponent)

		void Draw(class Renderer& r) override;

		void Read(const rapidjson::Value& value) override;

	private:
	};
}