//==============================================================================
#include "App.h"
#include "Log.h"

App App::instance;

//==============================================================================
App::App() {
}

//------------------------------------------------------------------------------
void App::onEvent(SDL_Event* Event) {
}

//------------------------------------------------------------------------------
bool App::init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    	Log("Unable to Init SDL: %s", SDL_GetError());
    	return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        Log("Unable to Init hinting: %s", SDL_GetError());
    }

    if((window = SDL_CreateWindow(
    	"My SDL Game",
    	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    	WindowWidth, WindowHeight, SDL_WINDOW_SHOWN)
    ) == NULL) {
    	Log("Unable to create SDL Window: %s", SDL_GetError());
    	return false;
    }

    primarySurface = SDL_GetWindowSurface(window);

    if((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
        Log("Unable to create renderer");
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

    return true;
}

//------------------------------------------------------------------------------
void App::loop() {
}

//------------------------------------------------------------------------------
void App::render() {
    SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

//------------------------------------------------------------------------------
void App::cleanup() {
	if(renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}

	if(window) {
		SDL_DestroyWindow(window);
		window = NULL;
	}

    SDL_Quit();
}

//------------------------------------------------------------------------------
int App::execute(int argc, char* argv[]) {
	if(!init()) return 0;

	SDL_Event Event;

	while(running) {
		while(SDL_PollEvent(&Event) != 0) {
			onEvent(&Event);

			if(Event.type == SDL_QUIT) running = false;
		}

		loop();
		render();

		SDL_Delay(1); // Breath
	}

	cleanup();

	return 1;
}

//==============================================================================
App* App::getInstance() { return &App::instance; }

int App::getWindowWidth()  { return WindowWidth; }
int App::getWindowHeight() { return WindowHeight; }

//==============================================================================
