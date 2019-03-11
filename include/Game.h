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
        void draw(Vector2i);
        void colisiones();


    protected:

    private:

        RenderWindow *win;
        Texture *tex_player,*textura1;;
        Player *player;
        Sprite *sprite1;
        Event e;
        vector<Enemy> enemigos;
        vector<Bullet> balas;
        Clock bullet_clock;
        Time bullet_cooldown;
        Vector2i winDim;
        sf::View view;
        sf::Vector2f position;


};

#endif // GAME_H
