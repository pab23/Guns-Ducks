#include "../include/Object.h"

using namespace std;

Object::Object(string type, Texture &tex)
{
    spr = new Sprite(tex);
    spr->setOrigin(32,32);
    if(type=="botijola")
    {
        tipo="b";
        spr->setTextureRect(IntRect(64, 64, 64, 64));

    }
    else if(type=="planchadito")
    {
        tipo="p";
        spr->setTextureRect(IntRect(0, 0, 64, 64));
    }
    else if(type=="ducknamyte")
    {
        tipo="d";
        spr->setTextureRect(IntRect(64,0, 64, 64));
    }
    else if(type=="pato")
    {
        tipo="m";
        spr->setTextureRect(IntRect(0, 64, 64, 64));
    }
    else if(type=="municionCarabina")
    {
        tipo="ammoC";
        spr->setTextureRect(IntRect(0, 128, 64, 64));
    }

    else if(type=="municionEscopeta")
    {
        tipo="ammoE";
        spr->setTextureRect(IntRect(64, 128, 64, 64));
    }



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

/*int Object::actua()
{
    return -1;
}*/
string Object::getTipo()
{
    return tipo;
}


