#include "Stage.h"
#include "../app/App.h"

void Stage::initStage(void)
{
    App *app = App::getInstance();

    fighterTail = &fighterHead;
    bulletTail = &bulletHead;

    initPlayer();

    bulletTexture = App::getInstance()->loadTexture(IMG_BULLET);
}

void Stage::initPlayer()
{
    fighterTail->next = &player;
    fighterTail = &player;

    player.x = 100;
    player.y = 100;
    player.texture = App::getInstance()->loadTexture(IMG_PLAYER);
    SDL_QueryTexture(player.texture, NULL, NULL, &player.w, &player.h);
}

void Stage::logic(void)
{
    doPlayer();

    doBullets();
}

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

// 发射炮弹
void Stage::fireBullet(void)
{
    Entity bullet;
    bulletTail->next = &bullet;
    bulletTail = &bullet;

    bullet.x = player.x;
    bullet.y = player.y;
    bullet.dx = PLAYER_BULLET_SPEED;
    bullet.health = 1;
    bullet.texture = bulletTexture;
    SDL_QueryTexture(bullet.texture, NULL, NULL, &bullet.w, &bullet.h);

    bullet.y += (player.h / 2) - (bullet.h / 2);

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

        if (b->x > WINDOW_WIDTH)
        {
            if (b == bulletTail)
                bulletTail = prev;

            prev->next = b->next;
            delete b; // TODO: 这里有可能报错
            b = prev;
        }

        prev = b;
    }
}

// 绘制Player 和 Bullets
void Stage::draw(void)
{
    drawPlayer();

    drawBullets();
}

void Stage::drawPlayer(void)
{
    App::getInstance()->blit(player.texture, player.x, player.y);
}

void Stage::drawBullets(void)
{
    Entity *b;

    for (b = bulletHead.next; b != NULL; b = b->next)
        App::getInstance()->blit(b->texture, b->x, b->y);
}

Stage::~Stage()
{
    Entity *b;
    for (b = bulletHead.next; b != NULL; b = b->next)
        delete b;

    if (fighterTail)
        delete fighterTail;

    if (bulletTail)
        delete bulletTail;
}