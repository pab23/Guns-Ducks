#ifndef BULLET_H
#define BULLET_H

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;
using namespace std;

class Bullet
{
    public:
        Bullet(Vector2f, Vector2i, float, Texture&, String arma);
        Bullet(const Bullet&);

        Bullet & operator=(const Bullet&);

        virtual ~Bullet();


        Sprite getSprite();
        CircleShape getBox();
        void move();
        FloatRect getBounds();
        Vector2f getPos();


    protected:

    private:
        Sprite *spr;
        CircleShape *box;
        Vector2i dir;
        float speed;
};

#endif // BULLET_H
