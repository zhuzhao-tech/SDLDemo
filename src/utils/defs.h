#ifndef __DEFS_H__
#define __DEFS_H__

#include "Log.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 1280 // 屏幕宽度
#define WINDOW_HEIGHT 720 // 屏幕高度

#define PLAYER_SPEED 4         // 飞机的速度
#define PLAYER_BULLET_SPEED 16 // 子弹的速度
#define MAX_KEYBOARD_KEYS 350  // 缓存的按键数组

//------------------------------------------------------------------------------

#define IMG_BULLET "../resources/drawable/bullet.png" // 子弹
#define IMG_PLAYER "../resources/drawable/player.png" // 飞机(玩家)

#endif