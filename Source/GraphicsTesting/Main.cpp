#include "StarFallEngine.h"
#include <memory>
#include <Renderer/Pipeline.h>
#include <Renderer/VertexBuffer.h>
#include <Renderer/IndexBuffer.h>
#include <Renderer/Shader.h>
#include <Renderer/Model.h>
#include <Renderer/Texture.h>
#include "Core/BatchRunner.h"
#include <Input/Input.h>
#include <Framework/Scene.h>
#include <Components/CameraComponent.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
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
    
    auto texture = ResourceManager().Get<Texture>("textures/spot_diffuse.png", renderer);
    auto vShader = std::make_shared<Shader>();
    auto fShader = std::make_shared<Shader>();
    (*vShader).Load("shaders/Phong.vert", renderer, 4);
    (*fShader).Load("shaders/Phong.frag", renderer, 3, 1);

    auto pipeline = std::make_shared<Pipeline>();
    pipeline->AddVertexBuffer(sizeof(Model::Vertex));
    pipeline->AddVertexAttribute(0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, offsetof(Model::Vertex, position));
    pipeline->AddVertexAttribute(1, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2, offsetof(Model::Vertex, texcoord));
    pipeline->AddVertexAttribute(2, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, offsetof(Model::Vertex, normal));
    pipeline->AddVertexAttribute(3, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, offsetof(Model::Vertex, tangent));
    pipeline->Create(*vShader, *fShader, renderer.GetGPUDevice(), renderer.GetWindow());
    


    SDL_Event SDLEvent;
    bool quit = false;
    
    while (!quit) {
        while (SDL_PollEvent(&SDLEvent)) {
            if (SDLEvent.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
            if (SDLEvent.type == SDL_EVENT_MOUSE_MOTION)
            {
                STR_Engine::Get().m_input.SetMouseRelative(SDLEvent.motion.xrel, SDLEvent.motion.yrel);
            }
            if (SDLEvent.type != SDL_EVENT_MOUSE_MOTION)
            {
                STR_Engine::Get().m_input.SetMouseRelative(0.0f, 0.0f);
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

#pragma region LiveShaderReload

        if (STR_Engine::Get().m_input.GetKeyPressed(Input::KeyCodes::VK_R))
        {
            RunBatch(
                SOLUTION_DIR "Tools\\compile_shaders.bat",
                { SOLUTION_DIR "Shaders", SOLUTION_DIR "Build\\Assets\\shaders" },
                true
            );
            (*vShader).~Shader();
            (*fShader).~Shader();
            (*vShader).Load("shaders/Phong.vert", renderer, 4);
            (*fShader).Load("shaders/Phong.frag", renderer, 3, 1);
            pipeline->Create(*vShader, *fShader, renderer.GetGPUDevice(), renderer.GetWindow());
        }

#pragma endregion

        renderer.BeginFrame();
        renderer.SetPipeline(*pipeline);

        //renderer.SetFragmentTexture(0, *texture);
        s.Draw(renderer);

        renderer.EndFrame();
    }

    STR_Engine::Get().Shutdown();
    
    return 0;
}