#pragma once
#include "RendererComponent.h"
#include <Resources/ResourceManager.h>
#include <Serialization/Json.h>

namespace STR_FALL
{
	class TileMapRendererComponent : public RendererComponent
	{
	public:
		TileMapRendererComponent() = default;
		TileMapRendererComponent(const TileMapRendererComponent& other)
		{
			m_tileMapName = other.m_tileMapName;
		}

		CLASS_PROTOTYPE(TileMapRendererComponent)

		void Start() override;
		void Draw(Renderer& r) override;
		void Read(const rapidjson::Value& value);

	private:
		std::string m_tileMapName;
		res_t<class TileMap> m_tileMap;

		std::vector<std::unique_ptr<class PhysicsBody>> m_physicsBodies;
	};
}