#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SDL2/SDL.h>

class Entity
{
public:
    float x; // 位置x坐标
    float y; // 位置y坐标

    int w; // 宽, 每次初始化后被赋值
    int h; // 高, 每次初始化后被赋值

    float dx; // 每次移动的delter 距离
    float dy; // 每次移动的delter 距离

    int health; // 生命值
    int reload; // 重新装弹的时间

    int side;   // 己方|敌方

    SDL_Texture *texture;

    Entity *next = NULL;

public:
    Entity();
    ~Entity();
};

#endif