#include "Bullet.h"

Bullet::Bullet(Vector2f pos, Vector2i p_dir, float radius)
{
    box = new CircleShape(radius);
    box->setFillColor(Color::Red);
    box->setPosition(pos);
    dir = p_dir;
    speed = 5;

}

Bullet::~Bullet()
{
    //dtor
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
    box->move(speedX, speedY);

}


CircleShape Bullet::getSprite()
{

    return *box;
}

