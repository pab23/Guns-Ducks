#include "../include/Enemy.h"

Enemy::Enemy(Texture &tex)
{
    speed = 5;
    spr = new Sprite(tex);
    spr->setOrigin(75/2,75/2);
    spr->setTextureRect(IntRect(0*75, 0*75, 75, 75));
    spr->setPosition(rand()%801,rand()%601);
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

FloatRect Enemy::getBounds()
{
    return spr->getGlobalBounds();
}

