#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Object.h"

#define kEnemy_reward 10

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
        void colisiones();
        void timeToString();
        void inZona();
        void inBad();



    protected:

    private:

        RenderWindow *win;
        Texture *tex_player;
        Player *player;
        Event e;
        vector<Enemy> enemigos;
        vector<Bullet> balas;
        vector<Object> objetos;
        Clock bullet_clock, general_clock, zone_clock;
        Time bullet_cooldown, general_timer, zone_timer;
        Vector2i winDim;
        Text *txt_time;
        Font *font;
        //Zonas
        RectangleShape *life_zone, *bad_zone;





};

#endif // GAME_H
