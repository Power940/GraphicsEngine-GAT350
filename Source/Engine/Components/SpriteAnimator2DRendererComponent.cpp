#include "pch.h"
#include "SpriteAnimator2DRendererComponent.h"
#include <Renderer/TextureFrames.h>
#include <Core/StringUtils.h>
#include "SpriteRenderer2DComponent.h"
#include <Serialization/Json.h>
#include <rapidjson/document.h>
#include <iostream>
#include <ostream>
#include <string>
#include <Core/Factory.h>
#include <Resources/ResourceManager.h>
#include <StarFallEngine.h>

namespace STR_FALL
{
	FACTORY_REG(SpriteAnimator2DRendererComponent)

	void SpriteAnimator2DRendererComponent::Start()
	{
		if (!m_defualtAnimationName.empty())
		{
			Play(m_defualtAnimationName);
		}
		else
		{
			Play(m_spriteAnimations.begin()->first);
		}
	}

	void SpriteAnimator2DRendererComponent::Update(float dt)
	{
		if (!m_spriteAnimation.m_textureFrames) { return; }

		m_frameTimer += dt;
		float frameTime = 1.0f / m_spriteAnimation.m_framesPerSecond;
		while (m_frameTimer >= frameTime)
		{
			m_frame++;
			if (m_spriteAnimation.m_loop)
			{
				m_frame %= m_spriteAnimation.m_textureFrames->GetTotalFrames();
			}
			else if (m_frame >= m_spriteAnimation.m_textureFrames->GetTotalFrames() - 1)
			{
				m_frame = m_spriteAnimation.m_textureFrames->GetTotalFrames() - 1;
			}

			m_frameTimer -= frameTime;
		}

		m_sourceRect = m_spriteAnimation.m_textureFrames->GetFrameRect(m_frame);
	}

	void SpriteAnimator2DRendererComponent::Play(const std::string& name)
	{
		if (EqualsIgnoreCase(name, m_spriteAnimation.m_name)) { return; }

		auto iter = m_spriteAnimations.find(ToLower(name));
		if (iter == m_spriteAnimations.end())
		{
			std::cerr << "could not find animation: " << name << std::endl;
			return;
		}

		m_spriteAnimation = iter->second;
		m_frame = 0;
		m_frameTimer = 0.0f;

		m_texture = m_spriteAnimation.m_textureFrames->GetTexture();
		m_sourceRect = m_spriteAnimation.m_textureFrames->GetFrameRect(m_frame);
	}

	bool SpriteAnimator2DRendererComponent::IsAnimationDone() const
	{
		return (m_frame == m_spriteAnimation.m_textureFrames->GetTotalFrames() - 1);
	}

	void SpriteAnimator2DRendererComponent::Read(const rapidjson::Value& value)
	{
		SpriteRenderer2DComponent::Read(value);

		JSON_READ(value, m_defualtAnimationName);

		if (JSON_HAS(value, "m_animations") && JSON_GET(value, "m_animations").IsArray())
		{
			for (auto& animatorValue : JSON_GET(value, "m_animations").GetArray())
			{
				SpriteAnimation spriteAnimation;

				std::string textureAnimationName;

				JSON_READ_NAME(animatorValue, "m_name", spriteAnimation.m_name);

				std::string m_textureFrames;
				JSON_READ(animatorValue, m_textureFrames);

				if (!m_textureFrames.empty())
				{
					spriteAnimation.m_textureFrames = ResourceManager::Instance().GetWithID<TextureFrames>(m_textureFrames, m_textureFrames, STR_Engine::m_renderer);
					if (!spriteAnimation.m_textureFrames)
					{
						std::cerr << "Could not load texture frames: " << m_textureFrames << std::endl;
					}
				}

				JSON_READ_NAME(animatorValue, "m_framesPerSecond", spriteAnimation.m_framesPerSecond);
				JSON_READ_NAME(animatorValue, "m_loop", spriteAnimation.m_loop);

				m_spriteAnimations[ToLower(spriteAnimation.m_name)] = spriteAnimation;
			}
		}

	}
}