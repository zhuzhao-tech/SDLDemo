#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "../../entity/Entity.h"

int collision(
    int x1, int y1, int w1, int h1,
    int x2, int y2, int w2, int h2);

int collision(
    const Entity *b, const Entity *e);

#endif