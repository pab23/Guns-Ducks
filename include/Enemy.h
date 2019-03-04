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

        Enemy(Texture &, float vel);
        ~Enemy();
        Sprite getSprite();
        FloatRect getBounds();
        Vector2f getPosition();
        Vector2i getDir();
        void setPosition(float x, float y);
        void setPosition(Vector2f vec);
        void move(Vector2f playerPosition);
        Vector2f getRandomPosition(Vector2i ventana);
        int RandomNumber( int inicio, int fin );




    protected:

    private:
        Sprite *spr;
        float speed;
        Vector2i dir;
        Vector2f direction;
        Vector2f normalizedDir;


};

#endif // ENEMY_H
