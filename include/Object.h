#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <ctime>

#include "SFML/Graphics.hpp"

#define SPR_SIZE 64

using namespace std;
using namespace sf;

class Object
{
    public:
        //CANONICAS
        Object(string type, Texture &);
        Object(const Object&);
        Object&operator=(const Object&);
        virtual ~Object();

        //GETTERS
        string getTipo();
        Sprite getSprite();
        RectangleShape getRect();
        Vector2f getPosition();
        FloatRect getBounds();
        FloatRect getBoundsBox();

        //SETTERS
        void setColor(int);

        //USER DEIFNED


    protected:

    private:
        string tipo;
        Sprite *spr;
        RectangleShape *box;
};




#endif // OBJECT_H
