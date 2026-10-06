#include "StarFallEngine.h"

#include <memory>

using namespace STR_FALL;

int const WINDOW_WIDTH = 1920;
int const WINDOW_HEIGHT = 1080;

int main()
{
    SetWorkingDirectory("Assets");

    int initCode = STR_Engine::Get().Initialize("Platformer Game", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;

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
            STR_Engine::Get().m_renderer.EndFrame();
        }
    }

    STR_Engine::Get().Shutdown();
    
    return 0;
}