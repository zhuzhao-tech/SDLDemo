#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SDL2/SDL.h>

class Player
{
public:
    int x;
    int y;

    SDL_Texture *texture;
};

#endif