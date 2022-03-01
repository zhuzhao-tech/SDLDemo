#include <SDL2/SDL.h>

#ifndef __APP_H__
#define __APP_H__

class App
{
private:
    static App instance;

    bool running = true;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *primarySurface = NULL;

    static const int WindowWidth = 1280;
    static const int WindowHeight = 720;

private:
    App();

    // Capture SDL Events
    void onEvent(SDL_Event *Event);

    // Initialize our SDL game / app
    bool init();

    // Logic loop
    void loop();

    // Render loop (draw)
    void render();

    // Free up resources
    void cleanup();

public:
    int execute(int argc, char *argv[]);

public:
    static App *getInstance();

    static int getWindowWidth();
    static int getWindowHeight();
};

#endif
