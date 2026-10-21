#include "StarFallEngine.h"
#include <memory>
#include <Renderer/Pipeline.h>
#include <Renderer/VertexBuffer.h>
#include <Renderer/IndexBuffer.h>
#include <Renderer/Shader.h>
#include <Renderer/Model.h>
#include <Renderer/Texture.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

using namespace STR_FALL;

int const WINDOW_WIDTH = 1920;
int const WINDOW_HEIGHT = 1080;



struct vertexUniform
{
    glm::mat4 mvp;
};





int main()
{
    SetWorkingDirectory("Assets");

    int initCode = STR_Engine::Get().Initialize("Super Epic Graphic Test", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;



    vertexUniform uniform;
    Transform3D t;
    Color tint = Color();
    glm::vec3 camPos = glm::vec3(0, 0, 5);
    glm::vec3 camRot = glm::vec3(0, 0, 5);
    float upRot = 0.0f;
    float leftRot = F_PI;


    auto model = ResourceManager().Get<Model>("models/spot.obj", STR_Engine::Get().m_renderer);
    auto texture = ResourceManager().Get<Texture>("textures/spot_diffuse.png", STR_Engine::Get().m_renderer);
    auto vshader = ResourceManager().Get<Shader>("shaders/unlit.vert", STR_Engine::Get().m_renderer, 1);
    auto fshader = ResourceManager().Get<Shader>("shaders/unlit.frag", STR_Engine::Get().m_renderer, 1, 1);

    auto pipeline = std::make_shared<Pipeline>();
    pipeline->AddVertexBuffer(sizeof(Model::Vertex));
    pipeline->AddVertexAttribute(0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, offsetof(Model::Vertex, position));
    pipeline->AddVertexAttribute(1, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2, offsetof(Model::Vertex, texcoord));
    pipeline->AddVertexAttribute(2, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, offsetof(Model::Vertex, normal));
    pipeline->AddVertexAttribute(3, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, offsetof(Model::Vertex, tangent));
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

        leftRot += STR_Engine::Get().m_input.GetKeyDiff(Input::KeyCodes::VK_LEFT, Input::KeyCodes::VK_RIGHT) * dt;
        upRot += STR_Engine::Get().m_input.GetKeyDiff(Input::KeyCodes::VK_UP, Input::KeyCodes::VK_DOWN) * dt;
        SDL_clamp(upRot, -F_HPI, F_HPI);
        camRot = glm::vec3(cosf(upRot) * sinf(leftRot), sinf(upRot), cosf(upRot) * cosf(leftRot));

        Vector3 dir = STR_Engine::Get().m_input.GetKeyDir(Input::KeyCodes::VK_D, Input::KeyCodes::VK_A, Input::KeyCodes::VK_W, Input::KeyCodes::VK_S).Normalize() * dt;
        float up = STR_Engine::Get().m_input.GetKeyDiff(Input::KeyCodes::VK_Q, Input::KeyCodes::VK_E) * dt;
        camPos.x += dir.m_x;
        camPos.z -= dir.m_y;
        camPos.y += up;
        

        auto view = glm::lookAtRH(camPos, camPos + camRot, glm::vec3(0, 1, 0));
        auto projection = glm::perspective(glm::radians(70.0f), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.01f, 50.0f);

        uniform.mvp = projection * view * t.GetMatrix();;

        STR_Engine::Get().m_renderer.BeginFrame();

        STR_Engine::Get().m_renderer.SetPipeline(*pipeline);
        STR_Engine::Get().m_renderer.SetVertexUniforms(0, &uniform, sizeof(uniform));
        STR_Engine::Get().m_renderer.SetFragmentUniforms(0, &tint, sizeof(tint));
        STR_Engine::Get().m_renderer.SetFragmentTexture(0, *texture);

        model->Draw(STR_Engine::Get().m_renderer);

        STR_Engine::Get().m_renderer.EndFrame();
    }

    STR_Engine::Get().Shutdown();
    
    return 0;
}