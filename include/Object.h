#ifndef OBJECT_H
#define OBJECT_H

#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Object
{
    public:
        Object(Texture &);
        virtual ~Object();
        Sprite getSprite();
        FloatRect getBounds();

    protected:

    private:
        Sprite *spr;
};

#endif // OBJECT_H
