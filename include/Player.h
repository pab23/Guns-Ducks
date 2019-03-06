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
        RectangleShape getRect();
        Vector2f getPosition();
        Vector2i getDir();
        FloatRect getBounds();
        FloatRect getBoundsBox();



    protected:

    private:
        Sprite *spr;
        RectangleShape *box;
        float speed;
        Vector2i dir;
};

#endif // PLAYER_H
