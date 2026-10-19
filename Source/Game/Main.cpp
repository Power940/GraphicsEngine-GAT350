#include "StarFallEngine.h"
#include <memory>
#include <Renderer/Pipeline.h>
#include <Renderer/VertexBuffer.h>
#include <Renderer/IndexBuffer.h>
#include <Renderer/Shader.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

using namespace STR_FALL;

int const WINDOW_WIDTH = 1920;
int const WINDOW_HEIGHT = 1080;

struct Vertex
{
    Vector3 pos;
    Color color;
};

struct vertexUniform
{
    glm::mat4 mvp;
};

vertexUniform uniform;
glm::vec3 camPos = glm::vec3(0, 0, 5);

std::vector<Vertex> vertices =
{
    Vertex{ {-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
    Vertex{ {0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
    Vertex{ {0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
    Vertex{ {-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
};

Transform3D t;

std::vector<uint32_t> indices = {0,1,2,2,3,0};

int main()
{
    SetWorkingDirectory("Assets");

    int initCode = STR_Engine::Get().Initialize("Super Epic Graphic Test", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;





    auto vb = std::make_shared<VertexBuffer>();
    vb->Create<Vertex>(vertices, STR_Engine::Get().m_renderer);

    auto ib = std::make_shared<IndexBuffer>();
    ib->Create(indices, STR_Engine::Get().m_renderer);

    auto vshader = ResourceManager().Get<Shader>("shaders/unlit.vert", STR_Engine::Get().m_renderer, 1);
    auto fshader = ResourceManager().Get<Shader>("shaders/unlit.frag", STR_Engine::Get().m_renderer, 1);

    auto pipeline = std::make_shared<Pipeline>();
    pipeline->AddVertexBuffer(sizeof(Vertex));
    pipeline->AddVertexAttribute(0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, offsetof(Vertex, pos));
    pipeline->AddVertexAttribute(1, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2, offsetof(Vertex, color));
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
        }
        STR_Engine::Get().Update();
        float time = STR_Engine::Get().m_time.GetTime();
        float dt = STR_Engine::Get().m_time.GetDeltaTime();

        Vector3 dir = STR_Engine::Get().m_input.GetKeyDir(Input::KeyCodes::VK_D, Input::KeyCodes::VK_A, Input::KeyCodes::VK_W, Input::KeyCodes::VK_S).Normalize() * dt;
        float up = STR_Engine::Get().m_input.GetKeyDiff(Input::KeyCodes::VK_Q, Input::KeyCodes::VK_E) * dt;
        camPos.x += dir.m_x;
        camPos.z -= dir.m_y;
        camPos.y += up;

        auto view = glm::lookAtRH(camPos, camPos + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

        float aspect = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);
        auto projection = glm::perspective(glm::radians(70.0f), aspect, 0.01f, 50.0f);

        uniform.mvp = projection * view * t.GetMatrix();;

        STR_Engine::Get().m_renderer.BeginFrame();

        STR_Engine::Get().m_renderer.SetPipeline(*pipeline);
        STR_Engine::Get().m_renderer.SetVertexBuffer(*vb);
        STR_Engine::Get().m_renderer.SetIndexBuffer(*ib);

        STR_Engine::Get().m_renderer.SetVertexUniforms(0, &uniform, sizeof(uniform));

        STR_Engine::Get().m_renderer.DrawIndex(*ib);

        STR_Engine::Get().m_renderer.EndFrame();
    }

    STR_Engine::Get().Shutdown();
    
    return 0;
}