#ifndef BULLET_H
#define BULLET_H

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;
using namespace std;

class Bullet
{
    public:
        Bullet(Vector2f, Vector2i, float);
        virtual ~Bullet();


        CircleShape getSprite();
        void move();
        FloatRect getBounds();

    protected:

    private:
        //Sprite *spr;
        CircleShape *box;
        Vector2i dir;
        float speed;
};

#endif // BULLET_H
