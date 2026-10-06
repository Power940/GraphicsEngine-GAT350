#pragma once
#include "SpriteRenderer2DComponent.h"
#include <Resources/ResourceManager.h>
#include <Serialization/Json.h>
#include <Framework/Object.h>
#include <Renderer/TextureFrames.h>
#include <Resources/Resource.h>
#include <rapidjson/document.h>
#include <map>
#include <string>

namespace STR_FALL
{
	class SpriteAnimator2DRendererComponent : public SpriteRenderer2DComponent
	{
	public:
		bool paused = false;

		struct SpriteAnimation
		{
			std::string m_name;
			float m_framesPerSecond = 10.0f;
			bool m_loop = true;
			res_t<class TextureFrames> m_textureFrames;
		};

		CLASS_PROTOTYPE(SpriteAnimator2DRendererComponent)

		void Start() override;
		void Update(float dt) override;
		void Play(const std::string& name);
		void Pause();
		unsigned int GetFrame() const { return m_frame; }
		bool IsAnimationDone() const;
		const std::string& GetAnimationName() const { return m_spriteAnimation.m_name; }
		void Read(const rapidjson::Value& value) override;

	private:
		unsigned int m_frame = 0;
		float m_frameTimer = 0.0f;

		std::string m_defualtAnimationName;
		SpriteAnimation m_spriteAnimation;
		std::map<std::string, SpriteAnimation> m_spriteAnimations;
	};
}