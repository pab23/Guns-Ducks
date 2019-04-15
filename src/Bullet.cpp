#include "../include/Bullet.h"


Bullet::Bullet(Vector2f pos, Vector2i p_dir, float radius, Texture &tex, String arma)
{
    spr = new Sprite(tex);
    box = new CircleShape(radius);
    box->setFillColor(Color::Red);

    dir = p_dir;
    speed = 50;
    spr->setTextureRect(IntRect(0, 0, 32, 32));
    spr->setScale(1,1);
    spr->setOrigin(spr->getGlobalBounds().width/2, spr->getGlobalBounds().height/2);


    if(arma=="Pistola")
    {
        spr->setTextureRect(IntRect(0, 0, 32, 32));

    }
    else if(arma=="Carabina")
    {
        spr->setTextureRect(IntRect(32, 0, 32, 32));
    }
    else if(arma=="Escopeta")
    {
        spr->setTextureRect(IntRect(0, 32, 32, 32));
    }


    if(dir.x==0 && dir.y==1)
    {
        spr->rotate(180);
    }
    else if(dir.x==1 && dir.y==0)
    {
        spr->rotate(90);
    }
    else if(dir.x==1 && dir.y==-1)
    {
        spr->rotate(45);
    }
    else if(dir.x==1 && dir.y==1)
    {
        spr->rotate(135);
    }

    else if(dir.x==-1 && dir.y==0)
    {
        spr->rotate(-90);
    }
    else if(dir.x==-1 && dir.y==-1)
    {
        spr->rotate(-45);
    }
    else if(dir.x==-1 && dir.y==1)
    {
        spr->rotate(-135);
    }
    spr->setPosition(pos.x-spr->getGlobalBounds().width/4, pos.y-spr->getGlobalBounds().height/4);




}

Bullet::Bullet(const Bullet& b)
{
    spr = b.spr;
    dir = b.dir;
    speed = b.speed;
}

Bullet & Bullet::operator=(const Bullet& b)
{
    if(this != &b)
    {
        if(spr != NULL)
            delete spr;
        if(b.spr != NULL)
            *spr = *b.spr;
        dir = b.dir;
        speed = b.speed;
    }
    return *this;
}


Bullet::~Bullet()
{
    delete spr;
    dir = {0,0};
    speed = 0;
}

void Bullet::move()
{
    float speedX, speedY;
    switch(dir.x)
    {
        case 1:
            speedX = speed;
        break;
        case -1:
            speedX = -speed;
        break;
        default:
            speedX = 0;
        break;
    }
    switch(dir.y)
    {
        case 1:
            speedY = speed;
        break;
        case -1:
            speedY = -speed;
        break;
        default:
            speedY = 0;
        break;
    }
    //cout<<"Bullet: "<<speedX<<","<<speedY<<endl;
    spr->move(speedX, speedY);
    box->move(speedX, speedY);

}


Sprite Bullet::getSprite()
{

    return *spr;
}

CircleShape Bullet::getBox()
{

    return *box;
}
Vector2f Bullet::getPos()
{
    return spr->getPosition();
}

FloatRect Bullet::getBounds(){
    return spr->getGlobalBounds();
}
