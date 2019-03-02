#include "../include/Object.h"

Object::Object(Texture &tex)
{
    spr = new Sprite(tex);
    spr->setOrigin(75/2,75/2);
    spr->setTextureRect(IntRect(3.5*75, 0*75, 75, 75));
    spr->setPosition(rand()%801,rand()%601);
}

Object::~Object()
{
    //dtor
}

Sprite Object::getSprite()
{
    return *spr;
}

FloatRect Object::getBounds()
{
    return spr->getGlobalBounds();
}
