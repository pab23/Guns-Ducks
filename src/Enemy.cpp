#include "../include/Enemy.h"

Enemy::Enemy(Texture &tex)
{
    speed = 2;
    spr = new Sprite(tex);
    spr->setOrigin(75/2,75/2);
    spr->setTextureRect(IntRect(0*75, 0*75, 75, 75));
    spr->setPosition(rand()%801,rand()%601);
    //direction = {0,0};


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

FloatRect Enemy::getBounds(){
    return spr->getGlobalBounds();
}

Vector2f Enemy::getPosition(){
    return spr->getPosition();
}
void Enemy::move(Vector2f playerPosition){

    direction = playerPosition - getPosition();
    normalizedDir.x = direction.x / (sqrt(pow(direction.x, 2) + pow(direction.y, 2)));
    normalizedDir.y = direction.y / (sqrt(pow(direction.x, 2) + pow(direction.y, 2)));

    Vector2f currentSpeed = normalizedDir * speed;

    spr->move(currentSpeed);




}

