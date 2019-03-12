#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "AnimatedSprite.h"
#include "Animation.h"

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



    protected:

    private:

        RenderWindow *win;
        Texture *tex_player, *tex_enemy;
        Player *player;
        Event e;
        vector<Enemy> enemigos;
        vector<Bullet> balas;
        Clock bullet_clock, enemy_clock,frame_clock;
        Time bullet_cooldown, enemy_timer;
        Vector2i winDim;
        bool primer, info;



};

#endif // GAME_H
