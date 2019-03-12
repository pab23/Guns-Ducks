#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Player
{
    public:
        Player(){}
        Player(Texture&);

        void move(int, int);

        Sprite getSprite();
        Vector2f getPosition();
        Vector2i getDir();
        CircleShape getCircle();
        FloatRect getBounds();
        FloatRect getBoundsBox();
        void setPosition(Vector2f vec);
        RectangleShape getRect();
        //void cambiarAnimacion();


    protected:

    private:
        Sprite *spr;
        RectangleShape *box;
        CircleShape *circle;//para que enemigos rodeen al player
        float speed;
        Vector2i dir;
};

#endif // PLAYER_H
