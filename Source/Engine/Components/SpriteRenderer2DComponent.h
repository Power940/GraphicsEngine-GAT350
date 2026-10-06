#pragma once
#include "RendererComponent.h"
#include <Core/Factory.h>
#include <Framework/Object.h>
#include <Math/Structs.h>
#include <Renderer/Renderer.h>
#include <Renderer/Texture.h>
#include <Resources/Resource.h>
#include <Resources/ResourceManager.h>
#include <Serialization/Json.h>
#include <rapidjson/document.h>
#include <string>
#include <StarFallEngine.h>


namespace STR_FALL
{
	class SpriteRenderer2DComponent : public RendererComponent
	{
	public:
		std::string m_textureName;
		res_t<Texture> m_texture;

		Rect2D m_sourceRect;
		Vector2 m_size = Vector2();
		Vector2 m_scale = Vector2(1.0f, 1.0f);
		Vector2 m_origin = Vector2(0.5f, 0.5f);
		float m_rot = 0.0f;
		bool m_flipH = false;


		CLASS_PROTOTYPE(SpriteRenderer2DComponent)

		void Start() override
		{
			if (!m_textureName.empty())
			{
				m_texture = ResourceManager::ResManager().GetWithID<Texture>(m_textureName.c_str(), m_textureName.c_str(), STR_Engine::m_renderer);

				if (m_texture)
				{
					m_size = m_texture->m_size;
				}
			}
		}
		
		virtual void Draw(class Renderer& r) override
		{
			if (m_sourceRect.m_w > 0 && m_sourceRect.m_h > 0)
			{
				r.RenderTexture(m_texture.get(), m_sourceRect, m_owner->m_transform.m_pos.m_x, m_owner->m_transform.m_pos.m_y, m_rot, m_scale.m_x, m_scale.m_y, m_flipH, m_origin);
			}
			else
			{
				r.RenderTexture(m_texture.get(), m_owner->m_transform.m_pos.m_x, m_owner->m_transform.m_pos.m_y, m_rot, m_scale.m_x, m_scale.m_y, m_flipH, m_origin);
			}
		}

		virtual void Read(const rapidjson::Value& value) override
		{
			RendererComponent::Read(value);

			JSON_READ(value, m_textureName);
			JSON_READ(value, m_flipH);
			JSON_READ(value, m_origin);
		}
	};

	FACTORY_REG(SpriteRenderer2DComponent)
}