#include "../include/Object.h"

using namespace std;

Object::Object(string type, Texture &tex, Vector2f pos)
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

    spr->setPosition(pos);

}
Object::Object(const Object& obj)
{
    tipo = obj.tipo;
    spr = obj.spr;

}
Object & Object::operator=(const Object& obj)
{
    if(this != &obj)
    {
        if(spr != NULL)
            delete spr;
        tipo = obj.tipo;
        spr = obj.spr;
    }
    return *this;
}
Object::~Object()
{
    tipo = "";
    if(spr != NULL)
        delete spr;
}

Sprite Object::getSprite()
{
    return *spr;
}


Vector2f Object::getPosition()
{
    return spr->getPosition();
}

FloatRect Object::getBounds()
{
    return spr->getGlobalBounds();
}



/*int Object::actua()
{
    return -1;
}*/
string Object::getTipo()
{
    return tipo;
}


