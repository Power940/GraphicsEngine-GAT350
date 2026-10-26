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
#include <cstdint>

using namespace STR_FALL;

int const WINDOW_WIDTH = 1920;
int const WINDOW_HEIGHT = 1080;

enum class LightType : uint8_t
{
    LIGHT_DIRECTIONAL,
    LIGHT_POINT,
    LIGHT_SPOT
};



struct VertexUniform
{
    glm::mat4 mvp;
    glm::mat4 model;
    glm::vec3 camPos;
};
struct LightUniform
{
    glm::vec3 position;
    LightType type;

    glm::vec3 direction;
    float padding2;

    glm::vec3 color;
    float intensity;

    glm::vec3 ambiant;
    float padding3;
};
struct MaterialUniform
{
    glm::vec2 tiling;
    glm::vec2 offset;
};





int main()
{
    SetWorkingDirectory("Assets");

    int initCode = STR_Engine::Get().Initialize("Super Epic Graphic Test", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;

    STR_Engine::Get().m_input.LockHideMouse(STR_Engine::Get().m_renderer.GetWindow());



    VertexUniform vertexUniform;
    LightUniform lightUniform{
        .position = glm::vec3(10.0f, 10.0f, 10.0f),
        .type = LightType::LIGHT_POINT,
        .direction = glm::vec3(0.0f, 0.5f, -0.5f),
        .color = glm::vec3(0.5f, 0.5f, 0.6f),
        .intensity = 1.0f,
        .ambiant = glm::vec3(0.75f)
    };
    MaterialUniform materialUnifrom{
        .tiling = glm::vec2(1.0f),
        .offset = glm::vec2(0.0f)
    };

    Transform3D t;
    t.m_scale = glm::vec3(0.1f);
    Color tint = Color();
    vertexUniform.camPos = glm::vec3(0, 0, 1);
    glm::vec3 camRot = glm::vec3(0, 0, 0);
    float upRot = 0.0f;
    float leftRot = F_PI;

    auto model = ResourceManager().Get<Model>("models/BadGuy.obj", STR_Engine::Get().m_renderer);
    auto texture = ResourceManager().Get<Texture>("textures/BadGuy_Material_BaseColor.png", STR_Engine::Get().m_renderer);
    auto vshader = ResourceManager().Get<Shader>("shaders/Gouraud.vert", STR_Engine::Get().m_renderer, 3);
    auto fshader = ResourceManager().Get<Shader>("shaders/Gouraud.frag", STR_Engine::Get().m_renderer, 1, 1);

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
            if (SDLEvent.type == SDL_EVENT_MOUSE_MOTION) {
                leftRot -= SDLEvent.motion.xrel * 0.003f;
                upRot -= SDLEvent.motion.yrel * 0.003f;

                upRot = (upRot < -F_HPI + 0.0001f) ? -F_HPI + 0.0001f : upRot;
                upRot = (upRot > F_HPI - 0.0001f) ? F_HPI - 0.0001f : upRot;
            }
        }

        STR_Engine::Get().Update();
        float time = STR_Engine::Get().m_time.GetTime();
        float dt = STR_Engine::Get().m_time.GetDeltaTime();

        //t.m_rot.x += F_HPI * dt;

        Vector3 dir = STR_Engine::Get().m_input.GetKeyDir(Input::KeyCodes::VK_A, Input::KeyCodes::VK_D, Input::KeyCodes::VK_W, Input::KeyCodes::VK_S).Normalize() * dt;
        float up = STR_Engine::Get().m_input.GetKeyDiff(Input::KeyCodes::VK_SPACE, Input::KeyCodes::VK_LCTRL) * dt;

        camRot = glm::vec3(cosf(upRot) * sinf(leftRot), sinf(upRot), cosf(upRot) * cosf(leftRot));
        vertexUniform.camPos.x += dir.m_x * cosf(leftRot) + dir.m_y * sinf(leftRot);
        vertexUniform.camPos.z += -dir.m_x * sinf(leftRot) + dir.m_y * cosf(leftRot);
        vertexUniform.camPos.y += up;

        //materialUnifrom.offset.x += dt;

        auto view = glm::lookAtRH(vertexUniform.camPos, vertexUniform.camPos + camRot, glm::vec3(0, 1, 0));
        auto projection = glm::perspective(glm::radians(70.0f), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.01f, 50.0f);
        vertexUniform.model = t.GetMatrix();
        vertexUniform.mvp = projection * view * vertexUniform.model;

        STR_Engine::Get().m_renderer.BeginFrame();
        STR_Engine::Get().m_renderer.SetPipeline(*pipeline);
        STR_Engine::Get().m_renderer.SetVertexUniforms(0, &vertexUniform, sizeof(vertexUniform));
        STR_Engine::Get().m_renderer.SetVertexUniforms(1, &lightUniform, sizeof(lightUniform));
        STR_Engine::Get().m_renderer.SetVertexUniforms(2, &materialUnifrom, sizeof(materialUnifrom));
        STR_Engine::Get().m_renderer.SetFragmentUniforms(0, &tint, sizeof(tint));
        STR_Engine::Get().m_renderer.SetFragmentTexture(0, *texture);
        model->Draw(STR_Engine::Get().m_renderer);
        STR_Engine::Get().m_renderer.EndFrame();
    }

    STR_Engine::Get().Shutdown();
    
    return 0;
}