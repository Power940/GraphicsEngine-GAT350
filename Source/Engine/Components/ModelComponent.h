#pragma once
#include "RendererComponent.h"
#include <Resources/Resource.h>

namespace STR_FALL
{
	class ModelComponent : public RendererComponent
	{
	public:
		CLASS_PROTOTYPE(ModelComponent)

		void Draw(class Renderer& r) override;

		void Read(const rapidjson::Value& value) override;

		std::vector<res_t<class MaterialInstance>> m_materials;

	private:
		res_t<class Model> m_model;
	};
}