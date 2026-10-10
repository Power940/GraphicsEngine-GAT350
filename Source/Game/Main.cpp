#include "StarFallEngine.h"
#include <memory>
#include <Renderer/Pipeline.h>
#include <Renderer/VertexBuffer.h>
#include <Renderer/Shader.h>

using namespace STR_FALL;

int const WINDOW_WIDTH = 1920;
int const WINDOW_HEIGHT = 1080;

struct Vertex
{
    float x, y, z;
};

std::vector<Vertex> vertices =
{
    Vertex{ -1.0f, -1.0f, 0.0f},
    Vertex{  1.0f, -1.0f, 0.0f},
    Vertex{  0.0f,  1.0f, 0.0f},
};

int main()
{
    SetWorkingDirectory("Assets");

    int initCode = STR_Engine::Get().Initialize("Platformer Game", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;





    auto vb = std::make_shared<VertexBuffer>();
    vb->Create<Vertex>(vertices, STR_Engine::Get().m_renderer.GetGPUDevice());

    auto vshader = ResourceManager().Get<Shader>("shaders/position.vert", STR_Engine::Get().m_renderer);
    auto fshader = ResourceManager().Get<Shader>("shaders/color.frag", STR_Engine::Get().m_renderer);

    auto pipeline = std::make_shared<Pipeline>();
    pipeline->AddVertexBuffer(sizeof(Vertex));
    pipeline->AddVertexAttribute(0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, offsetof(Vertex, x));
    pipeline->Create(*vshader.get(), *fshader.get(), STR_Engine::Get().m_renderer.GetGPUDevice(), STR_Engine::Get().m_renderer.GetWindow());





    SDL_Event SDLEvent;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&SDLEvent)) {
            if (SDLEvent.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
            STR_Engine::Get().Update();
            STR_Engine::Get().m_renderer.BeginFrame();

            STR_Engine::Get().m_renderer.SetPipeline(*pipeline);
            STR_Engine::Get().m_renderer.SetVertexBuffer(*vb);
            STR_Engine::Get().m_renderer.Draw(vb->GetVertexCount());

            STR_Engine::Get().m_renderer.EndFrame();
        }
    }

    STR_Engine::Get().Shutdown();
    
    return 0;
}