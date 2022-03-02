#include <SDL2/SDL.h>

#ifndef __APP_H__
#define __APP_H__

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    int health;
    SDL_Texture *texture;
} Entity;

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

    int up;
    int down;
    int left;
    int right;
    int fire;

private:
    App();

    // Capture SDL Events
    void onEvent(SDL_Event *event);

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

public:
    Entity player;
    Entity bullet;

    SDL_Texture *loadTexture(char *filename);

    void blit(SDL_Texture *textture, int x, int y);

public:
    void doKeyDown(SDL_KeyboardEvent *event);

    void doKeyUp(SDL_KeyboardEvent *event);
};

#endif
