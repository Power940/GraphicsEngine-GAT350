#include "pch.h"
#include "StarFallEngine.h"

namespace STR_FALL
{
    int STR_Engine::Initialize(const char* windowName, const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
    {
        m_renderer = Renderer();
        if (!m_renderer.Initialize(windowName, WINDOW_WIDTH, WINDOW_HEIGHT)) { return 1; }

        m_PS2D = ParticleSystem2D();
        if (!m_PS2D.Initialize()) { return 2; }

        m_input = Input();
        if (!m_input.Initialize()) { return 3; }

        m_audio = Audio();
        if (!m_audio.Initialize()) { return 4; }

        m_phys = Physics();
        if (!m_phys.Initialize()) { return 5; }

        m_time = Time();

        return 0;
    }
    void STR_Engine::Shutdown()
    {
        m_phys.Shutdown();
        m_audio.ShutDown();
        m_PS2D.Shutdown();
        m_renderer.ShutDown();
    }
    void STR_Engine::Update()
    {
        m_time.Tick();
        m_input.Update();
        m_audio.Update();
        m_phys.Update(m_time.GetDeltaTime());
        m_PS2D.Update(m_time.GetDeltaTime());
    }
};