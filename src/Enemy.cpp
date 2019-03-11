#include "../include/Enemy.h"

Enemy::Enemy(Texture &tex)
{
    speed = 5;
    spr = new Sprite(tex);
    spr->setOrigin(84/2,76/2);
    spr->setTextureRect(IntRect(1*84, 1*76, 84, 76));

    int randx = rand()%801;
    int randy = rand()%601;
    spr->setPosition(randx, randy);


    box = new RectangleShape({0.6*spr->getTextureRect().width,76/4});
    box->setFillColor(Color::Red);
    box->setOrigin(0.65*spr->getTextureRect().width/2,76/2);
    box->setPosition(randx, randy+76/1.8);
}

Enemy::~Enemy()
{
    /*if(spr != NULL)
        delete spr;*/
}

Sprite Enemy::getSprite()
{
    return *spr;
}

RectangleShape Enemy::getRect()
{
    return *box;
}

Vector2f Enemy::getPosition()
{
    return spr->getPosition();
}

FloatRect Enemy::getBounds(){
    return spr->getGlobalBounds();
}

FloatRect Enemy::getBoundsBox(){
    return box->getGlobalBounds();
}
void Enemy::setColor(int color)
{
    if(color == 0)
    box->setFillColor(Color::Green);
    else
    box->setFillColor(Color::Red);
}

