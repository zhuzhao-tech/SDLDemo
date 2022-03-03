#include "Stage.h"
#include "../app/App.h"
#include "../utils/collision/Collision.h"

void Stage::initStage(void)
{
    App *app = App::getInstance();

    fighterTail = &fighterHead;
    bulletTail = &bulletHead;

    initPlayer();

    bulletTexture = App::getInstance()->loadTexture(IMG_BULLET);
    enemyTexture = App::getInstance()->loadTexture(IMG_ENEMY);

    enemySpawnTimer = 0;
}

void Stage::initPlayer()
{
    fighterTail->next = &player;
    fighterTail = &player;

    player.x = 100;
    player.y = 100;
    player.side = SIDE_PLAYER;
    player.texture = App::getInstance()->loadTexture(IMG_PLAYER);
    SDL_QueryTexture(player.texture, NULL, NULL, &player.w, &player.h);

    // 缩小一下player的大小
    player.w = player.w / 2;
    player.h = player.h / 2;
}

//------------------------------------------------------------------------------

void Stage::logic(void)
{
    doPlayer();

    doFighters();

    doBullets();

    spawnEnemies();
}

//------------------------------------------------------------------------------

// 监听按键，同时移动Player & 发射炮弹
void Stage::doPlayer(void)
{
    App *app = App::getInstance();

    player.dx = player.dy = 0;
    if (player.reload > 0)
        player.reload--;

    if (app->keyboard[SDL_SCANCODE_UP])
        player.dy = -PLAYER_SPEED;

    if (app->keyboard[SDL_SCANCODE_DOWN])
        player.dy = PLAYER_SPEED;

    if (app->keyboard[SDL_SCANCODE_LEFT])
        player.dx = -PLAYER_SPEED;

    if (app->keyboard[SDL_SCANCODE_RIGHT])
        player.dx = PLAYER_SPEED;

    if (app->keyboard[SDL_SCANCODE_LCTRL] && player.reload == 0)
        fireBullet();

    player.x += player.dx;
    player.y += player.dy;
}

//------------------------------------------------------------------------------

// 发射炮弹
void Stage::fireBullet(void)
{
    Entity *bullet = new Entity;
    bulletTail->next = bullet;
    bulletTail = bullet;

    bullet->x = player.x;
    bullet->y = player.y;
    bullet->dx = PLAYER_BULLET_SPEED;
    bullet->dy = 0.f;
    bullet->health = 1;
    bullet->texture = bulletTexture;
    bullet->side = SIDE_PLAYER;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

    // 缩小一下bullet的大小
    bullet->w = bullet->w / 3;
    bullet->h = bullet->h / 3;

    bullet->y += (player.h / 2) - (bullet->h / 2);

    player.reload = 8;
}

// 炮弹位置移动
void Stage::doBullets(void)
{
    Entity *b, *prev;
    prev = &bulletHead;

    for (b = bulletHead.next; b != NULL; b = b->next)
    {
        b->x += b->dx;
        b->y += b->dy;

        // 1. b->x > WINDOW_DIDTH: b刚好从右侧移出
        // 2. b与Enemy发生碰撞的时候
        if (bulletHitFighter(b) || b->x > WINDOW_WIDTH)
        {
            if (b == bulletTail)
                bulletTail = prev;

            prev->next = b->next;
            delete b;
            b = prev;
        }

        prev = b;
    }
}

//------------------------------------------------------------------------------

// 产生敌人
void Stage::spawnEnemies(void)
{
    Entity *enemy;

    if (--enemySpawnTimer <= 0)
    {
        enemy = new Entity;
        fighterTail->next = enemy;
        fighterTail = enemy;

        enemy->x = WINDOW_WIDTH;
        enemy->y = rand() % WINDOW_HEIGHT;
        enemy->texture = enemyTexture;
        enemy->side = SIDE_ENEMY;
        enemy->health = 1;
        SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

        // 缩小一下enemy的大小
        enemy->w = enemy->w / 3;
        enemy->h = enemy->h / 3;

        enemy->dx = -(2 + (rand() % 4));
        enemySpawnTimer = 30 + (rand() % 60);
    }
}

// 敌人移动
void Stage::doFighters(void)
{
    Entity *e, *prev;
    prev = &fighterHead;

    for (e = fighterHead.next; e != NULL; e = e->next)
    {
        e->x += e->dx;
        e->y += e->dy;

        // 1. 不是当前的玩家 | NPC
        // 2. e刚好从屏幕左侧移出 | e的生命值为0
        if (e != &player && (e->x < -e->w || e->health == 0))
        {
            if (e == fighterTail)
                fighterTail = prev;

            prev->next = e->next;
            delete e;
            e = prev;
        }

        prev = e;
    }
}

//------------------------------------------------------------------------------

// 绘制Player 和 Bullets
void Stage::draw(void)
{
    drawPlayer();

    drawBullets();

    drawFighters();
}

void Stage::drawPlayer(void)
{
    App::getInstance()->blit(player.texture, player.x, player.y, player.w, player.h);
}

void Stage::drawBullets(void)
{
    Entity *b;

    for (b = bulletHead.next; b != NULL; b = b->next)
        App::getInstance()->blit(b->texture, b->x, b->y, b->w, b->h);
}

void Stage::drawFighters(void)
{
    Entity *e;

    for (e = fighterHead.next; e != NULL; e = e->next)
        App::getInstance()->blit(e->texture, e->x, e->y, e->w, e->h);
}

//------------------------------------------------------------------------------

int Stage::bulletHitFighter(Entity *b)
{
    Entity *e;

    for (e = fighterHead.next; e != NULL; e = e->next)
    {
        if (e->side != b->side && collision(b, e))
        {
            b->health = 0;
            e->health = 0;

            return 1;
        }
    }

    return 0;
}

//------------------------------------------------------------------------------

Stage::~Stage()
{
}