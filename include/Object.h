#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <ctime>

#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Object
{
    public:
        Object(Texture &);
        virtual ~Object();
        Sprite getSprite();
        RectangleShape getRect();
        Vector2f getPosition();
        FloatRect getBounds();
        FloatRect getBoundsBox();
        void setColor(int);

    protected:

    private:
        Sprite *spr;
        RectangleShape *box;
};

#endif // OBJECT_H
