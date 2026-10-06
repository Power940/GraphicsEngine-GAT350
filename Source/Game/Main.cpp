#include "StarFallEngine.h"
#include "PlatformerGame/PlatformerGame.h"
#include <memory>

using namespace STR_FALL;

int const WINDOW_WIDTH = 1920;
int const WINDOW_HEIGHT = 1080;

std::unique_ptr<PlatformerGame> game = std::make_unique<PlatformerGame>();

int main()
{
    SetWorkingDirectory("Assets");

    int initCode = STR_Engine::Get().Initialize("Platformer Game", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;

    game->Initialize();
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
        game->Update();
        game->Draw();
    }

    game.reset();

    STR_Engine::Get().Shutdown();
    
    return 0;
}