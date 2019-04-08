#include "../include/Bullet.h"


Bullet::Bullet(Vector2f pos, Vector2i p_dir, float radius)
{
    box = new CircleShape(radius);
    box->setFillColor(Color::Red);
    box->setPosition(pos);
    dir = p_dir;
    speed = 50;

}

Bullet::Bullet(const Bullet& b)
{
    box = b.box;
    dir = b.dir;
    speed = b.speed;
}

Bullet & Bullet::operator=(const Bullet& b)
{
    if(this != &b)
    {
        if(box != NULL)
            delete box;
        if(b.box != NULL)
            *box = *b.box;
        dir = b.dir;
        speed = b.speed;
    }
    return *this;
}


Bullet::~Bullet()
{
    delete box;
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
    box->move(speedX, speedY);

}


CircleShape Bullet::getSprite()
{

    return *box;
}
Vector2f Bullet::getPos()
{
    return box->getPosition();
}

FloatRect Bullet::getBounds(){
    return box->getGlobalBounds();
}

