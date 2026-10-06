#include "pch.h"
#include "SpriteAnimationRenderer2DComponent.h"
#include <Core/Factory.h>
#include <Resources/ResourceManager.h>
#include <Renderer/TextureFrames.h>
#include "StarFallEngine.h"
#include <Math/Structs.h>
#include <Renderer/Renderer.h>

namespace STR_FALL
{
	FACTORY_REG(SpriteAnimationRenderer2DComponent)

	void SpriteAnimationRenderer2DComponent::Start()
	{
		if (!m_textureFrameName.empty())
		{
			m_textureFrames = ResourceManager::ResManager().GetWithID<TextureFrames>(m_textureFrameName.c_str(), m_textureFrameName.c_str(), STR_Engine::m_renderer);
			if (m_textureFrames)
			{
				m_sourceRect = m_textureFrames->GetFrameRect(0);
				m_size = Vector2(m_sourceRect.m_w, m_sourceRect.m_h);
				m_texture = m_textureFrames->GetTexture();
			}
			if (!m_textureFrames)
			{
				std::cerr << "Could not load texture frames: " << m_textureFrameName << std::endl;
			}
		}
	}

	void SpriteAnimationRenderer2DComponent::Update(float dt)
	{
		m_frameTimer += dt;
		float frameTime = 1.0f / m_framesPerSecond;
		while (m_frameTimer >= frameTime)
		{
			m_frame++;
			if (m_loop)
			{
				m_frame %= m_textureFrames->GetTotalFrames();
			}
			else if (m_frame >= m_textureFrames->GetTotalFrames() - 1)
			{
				m_frame = m_textureFrames->GetTotalFrames() - 1;
			}

			m_frameTimer -= frameTime;
		}

		m_sourceRect = m_textureFrames->GetFrameRect(m_frame);
	}

	void SpriteAnimationRenderer2DComponent::Read(const rapidjson::Value& value)
	{
 		SpriteRenderer2DComponent::Read(value);

		JSON_READ(value, m_framesPerSecond);
		JSON_READ(value, m_loop);

		JSON_READ(value, m_textureFrameName);
	}
}