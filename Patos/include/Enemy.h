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
        FloatRect getBounds();

    protected:

    private:
        Sprite *spr;
        float speed;

};

#endif // ENEMY_H
