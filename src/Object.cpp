#include "../include/Object.h"

Object::Object(Texture &tex)
{
    spr = new Sprite(tex);
    spr->setOrigin(95/2,75/2);
    spr->setTextureRect(IntRect(3.5*75, 0*75, 75, 75));

    int randx = rand()%801;
    int randy = rand()%601;
    spr->setPosition(randx, randy);

    box = new RectangleShape({54,76/4});
    box->setFillColor(Color::Red);
    box->setOrigin(84/2,76/2);
    box->setPosition(randx, randy+76/1.8);
}

Object::~Object()
{
    //dtor
}

Sprite Object::getSprite()
{
    return *spr;
}

RectangleShape Object::getRect()
{
    return *box;
}

Vector2f Object::getPosition()
{
    return spr->getPosition();
}

FloatRect Object::getBounds()
{
    return spr->getGlobalBounds();
}

FloatRect Object::getBoundsBox(){
    return box->getGlobalBounds();
}

void Object::setColor(int color)
{
    if(color == 0)
    box->setFillColor(Color::Green);
    else
    box->setFillColor(Color::Red);
}




//BOTIJOLA


Botijola::~Botijola()
{
    //dtor
}





//PLANCHADITO

