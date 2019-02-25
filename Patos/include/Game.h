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
        void checkZonaVerde();



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
        Clock zona_clock;
        Time zona_cooldown;
        int * score;
        //Zona verde
        RectangleShape * verde;
        RectangleShape * life_bar;


};

#endif // GAME_H
