#pragma once
#include "SpriteRenderer2DComponent.h"
#include <Resources/Resource.h>
#include <Framework/Object.h>
#include <Math/Structs.h>
#include <Renderer/Renderer.h>
#include <Renderer/TextureFrames.h>
#include <rapidjson/document.h>
#include <string>


namespace STR_FALL
{
	class SpriteAnimationRenderer2DComponent : public SpriteRenderer2DComponent
	{
	public:
		float m_rot = 0.0f;
		Vector2 m_scale = Vector2(1.0f, 1.0f);
		bool flipH = false;

		CLASS_PROTOTYPE(SpriteAnimationRenderer2DComponent)

		void Start() override;
		virtual void Update(float dt) override;
		virtual void Read(const rapidjson::Value& value) override;


	private:
		float m_framesPerSecond = 1.0f;
		bool m_loop = true;
		unsigned int m_frame = 0;
		float m_frameTimer = 0.0f;

		res_t<class TextureFrames> m_textureFrames;
		std::string m_textureFrameName;
	};
}
