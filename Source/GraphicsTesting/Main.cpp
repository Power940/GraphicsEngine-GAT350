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



enum class LightType : uint32_t
{
    DIRECTIONAL,
    POINT,
    SPOT
};
struct MatrixUniform
{
    glm::mat4 mvp;
    glm::mat4 model;
};
struct LightUniform
{
    glm::vec3 position;
    LightType type;

    glm::vec3 direction;
    float innerCutoff;

    glm::vec3 color;
    float intensity;

    glm::vec3 ambient;
    float outerCutoff;
};
struct MaterialUniform
{
    glm::vec4 color;

    glm::vec2 tiling;
    glm::vec2 offset;

    float shininess;
    glm::vec3 padding1;
};
struct VertexUniform
{
    glm::vec3 camPos;
};



int main()
{
    SetWorkingDirectory("Assets");

    int initCode = STR_Engine::Get().Initialize("Super Epic Graphic Test", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;

    STR_Engine::Get().m_input.LockHideMouse(STR_Engine::Get().m_renderer.GetWindow());



    MatrixUniform matrixUniform;
    VertexUniform vertexUniform;
    LightUniform lightUniform {
        .position = glm::vec3(1.0f, 3.0f, 1.0f),
        .type = LightType::POINT,
        .direction = glm::vec3(0.0f, -1.0f, 0.0f),
        .innerCutoff = glm::cos(glm::radians(30.0f)),
        .color = glm::vec3(0.5f, 0.5f, 0.5f),
        .intensity = 1.0f,
        .ambient = glm::vec3(0.5f),
        .outerCutoff = glm::cos(glm::radians(50.0f))
    };
    MaterialUniform materialUnifrom{
        .color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        .tiling = glm::vec2(1.0f),
        .offset = glm::vec2(0.0f),
        .shininess = 200.0f
    };

    Transform3D t;
    glm::vec4 tint = glm::vec4(1.0f);

    vertexUniform.camPos = glm::vec3(0, 0, 2);
    glm::vec3 camRot = glm::vec3(0, 0, 0);
    float upRot = 0.0f;
    float leftRot = F_PI;

    auto model = ResourceManager().Get<Model>("models/sphere.obj", STR_Engine::Get().m_renderer);
    auto texture = ResourceManager().Get<Texture>("textures/BadGuy_Material_BaseColor.png", STR_Engine::Get().m_renderer);
    auto vshader = ResourceManager().Get<Shader>("shaders/Phong.vert", STR_Engine::Get().m_renderer, 1);
    auto fshader = ResourceManager().Get<Shader>("shaders/Phong.frag", STR_Engine::Get().m_renderer, 3, 1);

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

        glm::vec2 dir = STR_Engine::Get().m_input.GetKeyDir(Input::KeyCodes::VK_A, Input::KeyCodes::VK_D, Input::KeyCodes::VK_W, Input::KeyCodes::VK_S);
        if (glm::length(dir) > 0.0001f) { dir = glm::normalize(dir) * dt; }
        float up = STR_Engine::Get().m_input.GetKeyDiff(Input::KeyCodes::VK_SPACE, Input::KeyCodes::VK_LCTRL) * dt;
        if (STR_Engine::Get().m_input.GetKeyPressed(Input::KeyCodes::VK_0))
        {
            lightUniform.type = LightType::DIRECTIONAL;
        }
        else if (STR_Engine::Get().m_input.GetKeyPressed(Input::KeyCodes::VK_1))
        {
            lightUniform.type = LightType::POINT;
        }
        else if (STR_Engine::Get().m_input.GetKeyPressed(Input::KeyCodes::VK_2))
        {
            lightUniform.type = LightType::SPOT;
        }

        camRot = glm::vec3(cosf(upRot) * sinf(leftRot), sinf(upRot), cosf(upRot) * cosf(leftRot));
        vertexUniform.camPos.x += dir.x * cosf(leftRot) + dir.y * sinf(leftRot);
        vertexUniform.camPos.z += -dir.x * sinf(leftRot) + dir.y * cosf(leftRot);
        vertexUniform.camPos.y += up;

        auto view = glm::lookAtRH(vertexUniform.camPos, vertexUniform.camPos + camRot, glm::vec3(0, 1, 0));
        auto projection = glm::perspective(glm::radians(70.0f), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.01f, 50.0f);
        matrixUniform.model = t.GetMatrix();
        matrixUniform.mvp = projection * view * matrixUniform.model;

        STR_Engine::Get().m_renderer.BeginFrame();
        STR_Engine::Get().m_renderer.SetPipeline(*pipeline);

        STR_Engine::Get().m_renderer.SetVertexUniforms(0, &matrixUniform, sizeof(matrixUniform));

        STR_Engine::Get().m_renderer.SetFragmentUniforms(0, &vertexUniform, sizeof(vertexUniform));
        STR_Engine::Get().m_renderer.SetFragmentUniforms(1, &lightUniform, sizeof(lightUniform));
        STR_Engine::Get().m_renderer.SetFragmentUniforms(2, &materialUnifrom, sizeof(materialUnifrom));

        STR_Engine::Get().m_renderer.SetFragmentTexture(0, *texture);
        model->Draw(STR_Engine::Get().m_renderer);
        STR_Engine::Get().m_renderer.EndFrame();
    }

    STR_Engine::Get().Shutdown();
    
    return 0;
}