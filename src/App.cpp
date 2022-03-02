//==============================================================================
#include "App.h"
#include "Log.h"
#include <SDL2/SDL_image.h>
#include <iostream>

App App::instance;

//==============================================================================
App::App()
{
}

//------------------------------------------------------------------------------
void App::onEvent(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        doKeyDown(&event->key);
        break;

    case SDL_KEYUP:
        doKeyUp(&event->key);
        break;
    }
}

//------------------------------------------------------------------------------
bool App::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Log("Unable to Init SDL: %s", SDL_GetError());
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        Log("Unable to Init hinting: %s", SDL_GetError());
    }

    if ((window = SDL_CreateWindow(
             "My SDL Game",
             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
             WindowWidth, WindowHeight, SDL_WINDOW_SHOWN)) == NULL)
    {
        Log("Unable to create SDL Window: %s", SDL_GetError());
        return false;
    }

    primarySurface = SDL_GetWindowSurface(window);

    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL)
    {
        Log("Unable to create renderer");
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 96, 128, 255, 0xFF);

    //-----
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    player.x = 100;
    player.y = 100;
    player.texture = loadTexture("/home/mk/workLiu/demo/SDLDemo/resources/drawable/player.png");

    return true;
}

//------------------------------------------------------------------------------
void App::loop()
{
}

//------------------------------------------------------------------------------
void App::render()
{
    SDL_RenderClear(renderer);

    if (getInstance()->up && player.y - 4 > 0)
        player.y -= 4;

    if (getInstance()->down && player.y + 4 < WindowHeight)
        player.y += 4;

    if (getInstance()->left && player.x - 4 > 0)
        player.x -= 4;

    if (getInstance()->right && player.x + 4 < WindowWidth)
        player.x += 4;

    blit(player.texture, player.x, player.y);

    SDL_RenderPresent(renderer);
}

//------------------------------------------------------------------------------
void App::cleanup()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    SDL_Quit();
}

//------------------------------------------------------------------------------
int App::execute(int argc, char *argv[])
{
    if (!init())
        return 0;

    SDL_Event Event;

    while (running)
    {
        while (SDL_PollEvent(&Event) != 0)
        {
            onEvent(&Event);

            if (Event.type == SDL_QUIT)
                running = false;
        }

        loop();
        render();

        SDL_Delay(1); // Breath
    }

    cleanup();

    return 1;
}

//==============================================================================
App *App::getInstance() { return &App::instance; }

int App::getWindowWidth() { return WindowWidth; }
int App::getWindowHeight() { return WindowHeight; }

//==============================================================================

//------------------------------------------------------------------------------

SDL_Texture *App::loadTexture(char *filename)
{
    SDL_Texture *texture;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    texture = IMG_LoadTexture(renderer, filename);

    if (!texture)
    {
        Log("图片初始化失败了: %s", SDL_GetError());
    }

    return texture;
}

void App::blit(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

//------------------------------------------------------------------------------

void App::doKeyDown(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            getInstance()->up = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            getInstance()->down = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            getInstance()->left = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            getInstance()->right = 1;
        }
    }
}

void App::doKeyUp(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            getInstance()->up = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            getInstance()->down = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            getInstance()->left = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            getInstance()->right = 0;
        }
    }
}

//------------------------------------------------------------------------------