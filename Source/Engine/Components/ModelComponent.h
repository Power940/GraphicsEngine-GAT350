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

	private:
		res_t<class Model> m_model;
		std::vector<res_t<class MaterialInstance>> m_materials;
	};
}