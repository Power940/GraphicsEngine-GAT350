#pragma once
#include "Math/Constants.h"
#include "Core/Random.h"
#include "Math/Structs.h"
#include "Renderer/Renderer.h"
#include "Input/Input.h"
#include "Core/StarTime.h"
#include "Framework/GameObject.h"
#include "Audio/Audio.h"
#include "Framework/Scene.h"
#include "Core/file.h"
#include "Renderer/Text.h"
#include "Framework/Game.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Texture.h"
#include "Resources/ResourceManager.h"
#include "Core/StringUtils.h"
#include "Core/Factory.h"
#include "Serialization/Json.h"
#include "Physics/Physics.h"


namespace STR_FALL
{
	struct STR_Engine
	{
	public:
		static STR_Engine& Get() { static STR_Engine engine; return engine; }

		inline static Renderer m_renderer;
		inline static Input m_input;
		inline static Time m_time;
		inline static Audio m_audio;
		inline static ParticleSystem2D m_PS2D;
		inline static Physics m_phys;

		int Initialize(const char* windowName, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
		void Shutdown();
		void Update();

	private:
		STR_Engine() = default;
	};
};