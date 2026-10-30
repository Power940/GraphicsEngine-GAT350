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

#define VERIFY_16_BYTES_BOUDERIES(T) static_assert(sizeof(T) % 16 == 0);

using namespace STR_FALL;

int const WINDOW_WIDTH = 1920;
int const WINDOW_HEIGHT = 1080;
#define MAX_LIGHTS 8



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
struct Light
{
    LightType type;
    glm::vec3 position;

    glm::vec3 color;
    float intensity;

    glm::vec3 direction;
    float innerCutoff;

    float outerCutoff;
    glm::vec3 ambient;

    float range;
    glm::vec3 padding1;
};
struct LightsUniform
{
    Light lights[MAX_LIGHTS];
    uint32_t num_lights;
    glm::vec3 ambiant;
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
    float padding1;
};

VERIFY_16_BYTES_BOUDERIES(MatrixUniform)
VERIFY_16_BYTES_BOUDERIES(Light)
VERIFY_16_BYTES_BOUDERIES(LightsUniform)
VERIFY_16_BYTES_BOUDERIES(MaterialUniform)
VERIFY_16_BYTES_BOUDERIES(VertexUniform)



int main()
{
    SetWorkingDirectory("Assets");

    int initCode = STR_Engine::Get().Initialize("Super Epic Graphic Test", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;

    STR_Engine::Get().m_input.LockHideMouse(STR_Engine::Get().m_renderer.GetWindow());



    MatrixUniform matrixUniform;
    MatrixUniform lMatrixUniform;
    VertexUniform vertexUniform;
    Light light1{
        .type = LightType::POINT,
        .position = glm::vec3(1.0f, 1.0f, 1.0f),
        .color = glm::vec3(0.5f, 0.5f, 0.5f),
        .intensity = 1.0f,
        .direction = glm::vec3(-1.0f, -1.0f, -1.0f),
        .innerCutoff = glm::cos(glm::radians(30.0f)),
        .outerCutoff = glm::cos(glm::radians(35.0f)),
        .ambient = glm::vec3(0.5f),
        .range = 30.0f
    };
    Light light2{
        .type = LightType::POINT,
        .position = glm::vec3(1.0f, 1.0f, 1.0f),
        .color = glm::vec3(1.0f, 0.0f, 0.0f),
        .intensity = 1.0f,
        .direction = glm::vec3(1.0f, -1.0f, -1.0f),
        .innerCutoff = glm::cos(glm::radians(30.0f)),
        .outerCutoff = glm::cos(glm::radians(35.0f)),
        .ambient = glm::vec3(0.5f),
        .range = 30.0f
    };
    Light light3{
        .type = LightType::POINT,
        .position = glm::vec3(1.0f, 1.0f, 1.0f),
        .color = glm::vec3(0.0f, 0.0f, 1.0f),
        .intensity = 1.0f,
        .direction = glm::vec3(1.0f, -1.0f, 1.0f),
        .innerCutoff = glm::cos(glm::radians(30.0f)),
        .outerCutoff = glm::cos(glm::radians(35.0f)),
        .ambient = glm::vec3(0.5f),
        .range = 30.0f
    };
    MaterialUniform materialUnifrom{
        .color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        .tiling = glm::vec2(1.0f),
        .offset = glm::vec2(0.0f),
        .shininess = 20.0f
    };
    LightsUniform lightsUniform {
        .lights = { light1, light2, light3 },
        .num_lights = 3,
        .ambiant = glm::vec3(0.5f)
    };

    Transform3D t;
    t.m_scale = glm::vec3(0.2f);
    glm::vec4 tint = glm::vec4(1.0f);

    vertexUniform.camPos = glm::vec3(0, 3, 0);
    glm::vec3 camRot = glm::vec3(0, 0, 0);
    float upRot = 0.0f;
    float leftRot = F_PI;
    
    auto model = ResourceManager().Get<Model>("models/BadGuy.obj", STR_Engine::Get().m_renderer);
    auto texture = ResourceManager().Get<Texture>("textures/BadGuy_Material_BaseColor.png", STR_Engine::Get().m_renderer);
    auto vshader = ResourceManager().Get<Shader>("shaders/Phong.vert", STR_Engine::Get().m_renderer, 4);
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

        lightsUniform.lights[1].position = glm::eulerAngleY(time) * glm::vec4(0, 0, 10, 1);
        lightsUniform.lights[2].position = glm::eulerAngleX(time * 0.33f) * glm::vec4(0, 0, 10, 1);

        glm::vec2 dir = STR_Engine::Get().m_input.GetKeyDir(Input::KeyCodes::VK_A, Input::KeyCodes::VK_D, Input::KeyCodes::VK_W, Input::KeyCodes::VK_S);
        if (glm::length(dir) > 0.0001f) { dir = glm::normalize(dir) * dt; }
        float up = STR_Engine::Get().m_input.GetKeyDiff(Input::KeyCodes::VK_SPACE, Input::KeyCodes::VK_LCTRL) * dt;

        camRot = glm::vec3(cosf(upRot) * sinf(leftRot), sinf(upRot), cosf(upRot) * cosf(leftRot));
        vertexUniform.camPos.x += dir.x * cosf(leftRot) + dir.y * sinf(leftRot);
        vertexUniform.camPos.z += -dir.x * sinf(leftRot) + dir.y * cosf(leftRot);
        vertexUniform.camPos.y += up;

        auto view = glm::lookAtRH(vertexUniform.camPos, vertexUniform.camPos + camRot, glm::vec3(0, 1, 0));
        auto projection = glm::perspective(glm::radians(70.0f), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.01f, 1000.0f);
        matrixUniform.model = t.GetMatrix();
        matrixUniform.mvp = projection * view * matrixUniform.model;

        STR_Engine::Get().m_renderer.BeginFrame();
        STR_Engine::Get().m_renderer.SetPipeline(*pipeline);


        STR_Engine::Get().m_renderer.SetVertexUniforms(0, &matrixUniform, sizeof(matrixUniform));

        STR_Engine::Get().m_renderer.SetFragmentUniforms(0, &vertexUniform, sizeof(vertexUniform));
        STR_Engine::Get().m_renderer.SetFragmentUniforms(1, &lightsUniform, sizeof(lightsUniform));
        STR_Engine::Get().m_renderer.SetFragmentUniforms(2, &materialUnifrom, sizeof(materialUnifrom));

        STR_Engine::Get().m_renderer.SetFragmentTexture(0, *texture);
        model->Draw(STR_Engine::Get().m_renderer);


        STR_Engine::Get().m_renderer.EndFrame();
    }

    STR_Engine::Get().Shutdown();
    
    return 0;
}