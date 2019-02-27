#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

class Enemy
{
    public:
        Enemy(Texture &);
        ~Enemy();
        Sprite getSprite();
        FloatRect getBounds();
        Vector2f getPosition();
        void move(Vector2f playerPosition);




    protected:

    private:
        Sprite *spr;
        float speed;

        Vector2f direction;
        Vector2f normalizedDir;


};

#endif // ENEMY_H
