#pragma once
#include <memory>
#include "Scene.h"


namespace STR_FALL
{
	class Game
	{
	protected:
		std::unique_ptr<Scene> m_scene = nullptr;

	public:
		Game();
		virtual ~Game();
		Game(std::unique_ptr<Scene> scene) : m_scene(std::move(scene)) {}

		virtual bool Initialize() { return true; }
		virtual void Shutdown() {}
		virtual void Update() = 0;
		virtual void Draw() = 0;

		void SetScene(std::unique_ptr<Scene> scene) { m_scene = std::move(scene); }
	};
}