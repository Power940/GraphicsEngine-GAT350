#pragma once
#include "Math/Constants.h"
#include "Core/Random.h"
#include "Math/Structs.h"
#include "Renderer/Renderer.h"
#include "Input/Input.h"
#include "Core/StarTime.h"
#include "Framework/GameObject.h"
#include "Framework/Scene.h"
#include "Core/file.h"
#include "Resources/ResourceManager.h"
#include "Core/StringUtils.h"
#include "Core/Factory.h"
#include "Serialization/Json.h"


namespace STR_FALL
{
	struct STR_Engine
	{
	public:
		static STR_Engine& Get() { static STR_Engine engine; return engine; }

		inline static Renderer m_renderer;
		inline static Input m_input;
		inline static Time m_time;

		int Initialize(const char* windowName, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
		void Shutdown();
		void Update();

	private:
		STR_Engine() = default;
	};
};