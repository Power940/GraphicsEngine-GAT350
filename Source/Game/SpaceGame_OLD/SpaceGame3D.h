#pragma once
#include "StarFallEngine.h"
#include "Ship3D.h"
#include "Marker.h"

using namespace STR_FALL;

enum GameState
{
	MainMenu,
	Game
};

class SpaceGame3D : public Game
{
public:
	GameState currentState = GameState::MainMenu;
	Text* menuText;

	virtual bool Initialize()
	{
		SetWorkingDirectory("SpaceGame_OLD");

		m_scene = std::make_unique<Scene>();
		m_scene->m_game = this;

#pragma region GameObjectSetup

		m_scene->Load("Data/Scene.json");

		SeedRandom();
		for (int index = 0; index < 500; index++)
		{
			std::unique_ptr<Marker> marker = Factory::Instance().Create<Marker>("MarkerPrototype");
			marker->m_transform.m_pos = Vector3(static_cast<float>(RandomInt(2000, -2000)), static_cast<float>(RandomInt(2000, -2000)), static_cast<float>(RandomInt(2000, -2000)));
			marker->m_transform.m_rotMat = Matrix3::RotationXYZ(Vector3(RandomFloat(F_PI2), RandomFloat(F_PI2), RandomFloat(F_PI2)));
			marker->GetComponent<MeshRenderer3DComponent>()->UpdateMesh(marker->m_transform);

			m_scene->AddObject(std::move(marker));
		}

		for (int index = 0; index < 100; index++)
		{
			std::unique_ptr<Marker> marker = Factory::Instance().Create<Marker>("MarkerPrototype");
			marker->m_transform.m_pos = Vector3(static_cast<float>(RandomInt(20000, -20000)), static_cast<float>(RandomInt(20000, -20000)), static_cast<float>(RandomInt(20000, -20000)));
			marker->m_transform.m_rotMat = Matrix3::RotationXYZ(Vector3(RandomFloat(F_PI2), RandomFloat(F_PI2), RandomFloat(F_PI2)));
			marker->GetComponent<MeshRenderer3DComponent>()->UpdateMesh(marker->m_transform);
			marker->m_canBeHit = false;

			m_scene->AddObject(std::move(marker));
		}

#pragma endregion

		Camera3D* cam = &(m_scene->GetObjectName<Ship3D>("PlayerShip")->m_cam);
		STR_Engine::Get().m_renderer.SetCamera(cam);

		STR_Engine::m_audio.AddSound("shoot", "Shoot.mp3");

		menuText = new Text(ResourceManager::ResManager().GetWithID<Font>("title_font", "Fonts/VCR_OSD_MONO.ttf", 64.0f));
		menuText->Create(STR_Engine::m_renderer, "3D Ship Sim - Press Space to Start", Color());

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