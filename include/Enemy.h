#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Enemy
{
    public:
        Enemy(Texture &);
        ~Enemy();
        Sprite getSprite();
        RectangleShape getRect();
        Vector2f getPosition();
        FloatRect getBounds();
        FloatRect getBoundsBox();

    protected:

    private:
        Sprite *spr;
        RectangleShape *box;
        float speed;

};

#endif // ENEMY_H
