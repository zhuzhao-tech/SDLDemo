#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SDL2/SDL.h>

class Entity
{
public:
    float x;
    float y;

    int w;
    int h;

    float dx;
    float dy;

    int health;
    int reload;

    SDL_Texture *texture;

    Entity *next;

public:
    Entity();
    ~Entity();
};

#endif