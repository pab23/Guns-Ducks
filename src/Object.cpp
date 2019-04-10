#include "../include/Object.h"

using namespace std;

Object::Object(string type, Texture &tex)
{
    spr = new Sprite(tex);
    spr->setOrigin(SPR_SIZE/2,SPR_SIZE/2);
    if(type=="botijola")
    {
        tipo="b";
        spr->setTextureRect(IntRect(SPR_SIZE, SPR_SIZE, SPR_SIZE, SPR_SIZE));

    }
    else if(type=="planchadito")
    {
        tipo="p";
        spr->setTextureRect(IntRect(0, 0, SPR_SIZE, SPR_SIZE));
    }
    else if(type=="ducknamyte")
    {
        tipo="d";
        spr->setTextureRect(IntRect(SPR_SIZE,0, SPR_SIZE, SPR_SIZE));
    }
    else if(type=="pato")
    {
        tipo="m";
        spr->setTextureRect(IntRect(0, SPR_SIZE, SPR_SIZE, SPR_SIZE));
    }
    else if(type=="municionCarabina")
    {
        tipo="ammoC";
        spr->setTextureRect(IntRect(0, SPR_SIZE*2, SPR_SIZE, SPR_SIZE));
    }

    else if(type=="municionEscopeta")
    {
        tipo="ammoE";
        spr->setTextureRect(IntRect(SPR_SIZE, SPR_SIZE*2, SPR_SIZE, SPR_SIZE));
    }



    int randx = rand()%801;
    int randy = rand()%601;
    spr->setPosition(randx, randy);

    box = new RectangleShape({54,76/4});
    box->setFillColor(Color::Red);
    box->setOrigin(84/2,76/2);
    box->setPosition(randx, randy+76/1.8);
}
Object::Object(const Object& obj)
{
    tipo = obj.tipo;
    spr = obj.spr;
    box = obj.box;
}
Object & Object::operator=(const Object& obj)
{
    if(this != &obj)
    {
        if(spr != NULL)
            delete spr;
        if(box != NULL)
            delete box;
        tipo = obj.tipo;
        spr = obj.spr;
        box = obj.box;
    }
    return *this;
}
Object::~Object()
{
    tipo = "";
    if(spr != NULL)
        delete spr;
    if(box != NULL)
        delete box;
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


