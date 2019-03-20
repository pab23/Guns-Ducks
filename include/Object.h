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
        Object(string type, Texture &);
        string getTipo();
        virtual ~Object();
        Sprite getSprite();
        RectangleShape getRect();
        Vector2f getPosition();
        FloatRect getBounds();
        FloatRect getBoundsBox();
        void setColor(int);


    protected:

    private:
        string tipo;
        Sprite *spr;
        RectangleShape *box;
};




#endif // OBJECT_H
