#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "AnimatedSprite.h"
#include "Animation.h"
#include "Object.h"
#include "Gun.h"

#define kEnemy_reward 10
#define UPDATE_TICK_TIME 1000/15

using namespace sf;
using namespace std;

class Game
{
    public:
        Game(Vector2i);

        void gameLoop();
        void loadTextures();
        void listenKeyboard();
        void draw();
        void moverEnemigos();
        void crearEnemy();
        void crearAnimaciones();
        void colisiones();
        void colisionBox();
        void timeToString();
        void inZona();
        void update();



    protected:

    private:

        RenderWindow *win;
        Texture *tex_player, *tex_enemy, *tex_object;
        Player *player;
        Event e;
        vector<Enemy> enemigos;
        vector<Bullet> balas;
        vector<Object> objetos;
        Clock bullet_clock, general_clock, zone_clock,  enemy_clock, frame_clock;
        Time bullet_cooldown, enemy_timer, general_timer, zone_timer, frame_timer;
        Vector2i winDim;
        bool primer, info;
        Text *txt_time;
        Font *font;
        RectangleShape *life_zone;





};

#endif // GAME_H
