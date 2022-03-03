#ifndef __STAGE_H__
#define __STAGE_H__

#include "../utils/defs.h"
#include "../entity/Entity.h"

class Stage
{
public:
    Entity player;

    Entity fighterHead;
    Entity *fighterTail;

    Entity bulletHead;
    Entity *bulletTail;

    SDL_Texture *bulletTexture;
    SDL_Texture *enemyTexture;

    int enemySpawnTimer = 0;

public:
    Stage() {}
    ~Stage();

    void initStage(void);

    void logic(void);

    void draw(void);

private:
    void initPlayer();

    void doPlayer(void);

    //------

    void doFighters(void);

    void spawnEnemies(void);

    //------

    void doBullets(void);

    void fireBullet(void);

    //------

    void drawPlayer(void);

    void drawBullets(void);

    void drawFighters(void);

    //------

    int bulletHitFighter(Entity *b);

    //------

    
};

#endif