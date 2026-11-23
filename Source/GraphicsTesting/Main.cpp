#include "StarFallEngine.h"
#include "Core/BatchRunner.h"
#include <Input/Input.h>
#include <Framework/Scene.h>
#include "Core/Helper.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <Framework/GameObject.h>
#include <Renderer/Shader.h>
#include <Renderer/Material.h>


using namespace STR_FALL;

int constexpr WINDOW_WIDTH = 1920;
int constexpr WINDOW_HEIGHT = 1080;

int main()
{
    SetWorkingDirectory("Assets");

    int initCode = STR_Engine::Get().Initialize("Super Epic Graphic Test", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;
    Renderer& renderer = STR_Engine::Get().m_renderer;
    SeedRandom();

    STR_Engine::Get().m_input.LockHideMouse(renderer.GetWindow());

    RunBatch(
        SOLUTION_DIR "Tools\\compile_shaders.bat",
        { SOLUTION_DIR "Shaders", SOLUTION_DIR "Build\\Assets\\shaders" },
        true
    );
    
    
    Scene s;
    s.Load("scenes/scene.json");

    for (int i = 0; i < 20; i++)
    {
        std::unique_ptr<GameObject> temp1 = Factory::Instance().Create<GameObject>("protoTree");
        temp1->IncrementTransformPos(glm::vec3(RandomFloat(50.0f, -50.0f), 0, RandomFloat(50.0f, -50.0f)));
        s.AddObject(std::move(temp1));

        std::unique_ptr<GameObject> temp2 = Factory::Instance().Create<GameObject>("protoVineTree");
        temp2->IncrementTransformPos(glm::vec3(RandomFloat(50.0f, -50.0f), 0, RandomFloat(50.0f, -50.0f)));
        s.AddObject(std::move(temp2));
    }

    for (int i = 0; i < 10; i++)
    {
        std::unique_ptr<GameObject> temp1 = Factory::Instance().Create<GameObject>("protoFox");
        temp1->IncrementTransformPos(glm::vec3(RandomFloat(50.0f, -50.0f), 0, RandomFloat(50.0f, -50.0f)));
        temp1->SetTransformRotation(glm::vec3(0, RandomFloat(F_PI2, 0.0f), 0));
        s.AddObject(std::move(temp1));
    }

    std::unique_ptr<GameObject> moon1 = Factory::Instance().Create<GameObject>("protoMoon");
    std::unique_ptr<GameObject> moon2 = Factory::Instance().Create<GameObject>("protoMoon");
    moon1->SetTransform(glm::vec3(-17.817, 25.7734, 22.0311));
    moon2->SetTransform(glm::vec3(6.90852, 22.5598, 21.043));
    s.AddObject(std::move(moon1));
    s.AddObject(std::move(moon2));


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
                if (STR_Engine::Get().m_input.IsMouseLocked())
                {
                    STR_Engine::Get().m_input.SetMouseRelative(SDLEvent.motion.xrel, SDLEvent.motion.yrel);
                }
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
        if (STR_Engine::Get().m_input.GetKeyPressed(Input::KeyCodes::VK_P))
        {
            glm::vec3 cam = s.GetObjectName<GameObject>("camera")->m_transform.m_pos;
            MultiPrintln(" | ", cam.x, cam.y, cam.z);
        }
        if (STR_Engine::Get().m_input.GetKeyPressed(Input::KeyCodes::VK_R))
        {
            RunBatch(
                SOLUTION_DIR "Tools\\compile_shaders.bat",
                { SOLUTION_DIR "Shaders", SOLUTION_DIR "Build\\Assets\\shaders" },
                true
            );
            for (Shader* shader : ResourceManager::ResManager().GetAllOfType<Shader>())
            {
                shader->Reload();
            }
            for (Material* shader : ResourceManager::ResManager().GetAllOfType<Material>())
            {
                shader->RecreatePipeline(renderer.GetWindow());
            }
        }

        STR_Engine::Get().m_editor.BeginFrame();
        STR_Engine::Get().m_editor.Update(s);

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