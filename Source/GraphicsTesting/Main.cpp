#include "StarFallEngine.h"
#include "Core/BatchRunner.h"
#include <Input/Input.h>
#include <Framework/Scene.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <Framework/GameObject.h>


using namespace STR_FALL;

int constexpr WINDOW_WIDTH = 1920;
int constexpr WINDOW_HEIGHT = 1080;

int main()
{
    SetWorkingDirectory("Assets");

    int initCode = STR_Engine::Get().Initialize("Super Epic Graphic Test", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;
    Renderer& renderer = STR_Engine::Get().m_renderer;

    STR_Engine::Get().m_input.LockHideMouse(renderer.GetWindow());

    RunBatch(
        SOLUTION_DIR "Tools\\compile_shaders.bat",
        { SOLUTION_DIR "Shaders", SOLUTION_DIR "Build\\Assets\\shaders" },
        true
    );
    
    
    Scene s;
    s.Load("scenes/scene.json");


    SDL_Event SDLEvent;
    bool quit = false;
    
    while (!quit) {
        while (SDL_PollEvent(&SDLEvent)) {

            STR_Engine::Get().m_editor.ProcessEvent(SDLEvent);

            if (SDLEvent.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
            if (SDLEvent.type == SDL_EVENT_MOUSE_MOTION)
            {
                STR_Engine::Get().m_input.SetMouseRelative(SDLEvent.motion.xrel, SDLEvent.motion.yrel);
            }
        }

        STR_Engine::Get().Update();
        float time = STR_Engine::Get().m_time.GetTime();
        float dt = STR_Engine::Get().m_time.GetDeltaTime();
        s.Update(dt);

        if (STR_Engine::Get().m_input.GetKeyPressed(Input::KeyCodes::VK_ESCAPE))
        {
            STR_Engine::Get().m_input.UnlockShowMouse(STR_Engine::Get().m_renderer.GetWindow());
        }
        if (STR_Engine::Get().m_input.GetKeyPressed(Input::KeyCodes::VK_LALT))
        {
            STR_Engine::Get().m_input.LockHideMouse(STR_Engine::Get().m_renderer.GetWindow());
        }

        STR_Engine::Get().m_editor.BeginFrame();
        STR_Engine::Get().m_editor.Update();

        renderer.BeginFrame();

        s.Draw(renderer);

        STR_Engine::Get().m_renderer.EndRenderPass();
        STR_Engine::Get().m_editor.Draw(renderer);

        renderer.EndFrame();

        STR_Engine::Get().m_input.SetMouseRelative(0.0f, 0.0f);
    }

    STR_Engine::Get().Shutdown();
    
    return 0;
}