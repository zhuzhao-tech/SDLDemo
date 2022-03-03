//==============================================================================
#include "App.h"
#include <SDL2/SDL_image.h>
#include <iostream>

App App::instance;

App *App::getInstance() { return &App::instance; }

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

        capFrameRate(&then, &remainder);
    }

    cleanup();

    return 1;
}

//==============================================================================

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

    // 创建窗口
    if ((window = SDL_CreateWindow(
             "My SDL Game",
             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
             WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
    {
        Log("Unable to create SDL Window: %s", SDL_GetError());
        return false;
    }

    primarySurface = SDL_GetWindowSurface(window);

    // 渲染器
    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL)
    {
        Log("Unable to create renderer");
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 96, 128, 255, 0xFF);

    // 设置可以加载图片
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    stage.initStage();

    return true;
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

void App::loop()
{
}

//------------------------------------------------------------------------------
void App::render()
{
    SDL_RenderClear(renderer);

    stage.logic();
    stage.draw();

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

App::~App()
{
}

//------------------------------------------------------------------------------

void App::capFrameRate(long *then, float *remainder)
{
    long wait, frameTime;
    wait = 16 + *remainder;
    *remainder -= (int)*remainder;

    frameTime = SDL_GetTicks() - *then;
    wait -= frameTime;

    if (wait < 1)
        wait = 1;

    SDL_Delay(wait);

    *remainder += 0.667;
    *then = SDL_GetTicks();
}

//------------------------------------------------------------------------------

SDL_Texture *App::loadTexture(const char *filename)
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

void App::blit(SDL_Texture *texture, int x, int y, int w, int h)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

//------------------------------------------------------------------------------

void App::doKeyDown(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
    {
        getInstance()->keyboard[event->keysym.scancode] = 1;
    }
}

void App::doKeyUp(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
    {
        getInstance()->keyboard[event->keysym.scancode] = 0;
    }
}

//------------------------------------------------------------------------------