#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

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


    protected:

    private:

        RenderWindow *win;
        Texture *tex_player;
        Player *player;
        Event e;
        vector<Enemy> enemigos;
        vector<Bullet> balas;
        Clock bullet_clock;
        Time bullet_cooldown;


};

#endif // GAME_H
