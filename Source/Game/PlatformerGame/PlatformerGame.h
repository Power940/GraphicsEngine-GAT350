#pragma once
#include "StarFallEngine.h"
#include <Core/File.h>
#include "PlayerController.h"
#include "Platform.h"

using namespace STR_FALL;

enum GameState
{
	MainMenu,
	Game
};

class PlatformerGame : public Game
{
public:
	GameState currentState = GameState::MainMenu;
	Text* menuText;

	virtual bool Initialize()
	{
		SetWorkingDirectory("PlatformerGame");

		m_scene = std::make_unique<Scene>();
		m_scene->m_game = this;

#pragma region GameObjectSetup

		m_scene->Load("Scenes/Level1.json");

		SeedRandom();
		for (int index = 0; index < 50; index++)
		{
			std::unique_ptr<Platform> platform = Factory::Instance().Create<Platform>("PlatformPrototype");
			platform->m_transform.m_pos = Vector3(static_cast<float>(RandomInt(500, -500)), static_cast<float>(RandomInt(500, -500)), static_cast<float>(RandomInt(500, -500)));
			m_scene->AddObject(std::move(platform));
		}

#pragma endregion

		Camera3D* cam = &(m_scene->GetObjectName<PlayerController>("player")->m_cam);
		STR_Engine::Get().m_renderer.SetCamera(cam);

		menuText = new Text(ResourceManager::ResManager().GetWithID<Font>("title_font", "Fonts/VCR_OSD_MONO.ttf", 64.0f));
		menuText->Create(STR_Engine::m_renderer, "3D Platformer - Press Space to Start", Color());

		return true;
	}

	virtual void Shutdown()
	{
		STR_Engine::Get().Shutdown();
	}

	virtual void Update()
	{
		STR_Engine::Get().Update();

		if (currentState == GameState::MainMenu)
		{
			if (STR_Engine::m_input.GetKeyPressed(Input::VK_SPACE))
			{
				currentState = GameState::Game;
			}
		}
		else if (currentState == GameState::Game)
		{
			m_scene->Update(STR_Engine::m_time.GetDeltaTime());
		}
	}

	virtual void Draw()
	{
		if (currentState == GameState::MainMenu)
		{
			STR_Engine::m_renderer.Clear();
			menuText->Draw(STR_Engine::m_renderer, 100.0f, 100.0f);
			STR_Engine::m_renderer.Present();
		}
		else if (currentState == GameState::Game)
		{
			STR_Engine::m_renderer.Clear();
			m_scene->Draw(STR_Engine::m_renderer);
			STR_Engine::m_renderer.Present();
		}
	}
};