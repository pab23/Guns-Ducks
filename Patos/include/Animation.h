#ifndef ANIMATION_H
#define ANIMATION_H


#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Animation
{
public:
    Animation(Texture, int);
    void changePos();
    void changeSprite(int, int);
    Sprite getSprite();
    void setPosition(float,float);
    void setPosition(Vector2f);
    Vector2f getPosition();
    FloatRect getBounds();
    Vector2f getRandomPosition(Vector2i ventana);
    int RandomNumber( int inicio, int fin );




private:
    Sprite matrix[4][8];
    Texture anim_tex;
    int pos;
    int col;
    Sprite *spr;

};

#endif // ANIMATION_INCLUDE
