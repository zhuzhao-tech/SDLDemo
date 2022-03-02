#include "../utils/defs.h"
#include "../entity/Entity.h"
#include "../stage/Stage.h"

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

    long then;
    float remainder;

    Stage stage;

public:
    int keyboard[MAX_KEYBOARD_KEYS];

private:
    App() {}

    ~App();

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

    // 60fps
    void capFrameRate(long *then, float *remainder);

public:
    static App *getInstance();

    int execute(int argc, char *argv[]);

public:
    SDL_Texture *loadTexture(const char *filename);

    void blit(SDL_Texture *textture, int x, int y);

public:
    void doKeyDown(SDL_KeyboardEvent *event);

    void doKeyUp(SDL_KeyboardEvent *event);
};

#endif
