#ifndef ANIMATION_H
#define ANIMATION_H


#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "../include/Animation.h"

using namespace sf;
using namespace std;

class Animation
{
public:
    Animation(Texture, int);

    Sprite getSprite();

    Vector2f getRandomPosition(Vector2i ventana);
    int RandomNumber( int inicio, int fin );
    ///////////
    void changePos(Vector2i, int, Vector2f);
    void changeSprite(int, int, Vector2f);





private:
    Sprite matrix[4][8];
    Texture anim_tex;
    int pos;
    int col;
    Sprite *spr;
    Vector2i dir;

};

#endif // ANIMATION_INCLUDE
