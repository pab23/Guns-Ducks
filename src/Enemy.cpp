#include "../include/Enemy.h"

Enemy::Enemy(Texture &tex, float vel)
{
    speed = vel;
    spr = new Sprite(tex);
    spr->setOrigin(75/2,75/2);
    spr->setTextureRect(IntRect(0*75, 0*75, 75, 75));
    spr->setPosition(rand()%801,rand()%601);
    dir ={0,1};
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

Vector2i Enemy::getDir()
{
    return dir;
}

void Enemy::setPosition(float x, float y){
    spr->setPosition(x,y);
}
void Enemy::move(Vector2f playerPosition){

    direction = playerPosition - getPosition();
    normalizedDir.x = direction.x / (sqrt(pow(direction.x, 2) + pow(direction.y, 2)));
    normalizedDir.y = direction.y / (sqrt(pow(direction.x, 2) + pow(direction.y, 2)));
    Vector2f currentSpeed = normalizedDir * speed;
    spr->move(currentSpeed);

    if(direction.x < 0)
        dir.x = -1;
    else if(direction.x < 1.0)
        dir.x = 0;
    else dir.x = 1;

        if(direction.y < 0)
        dir.y = -1;
    else if(direction.y < 1.0)
        dir.y = 0;
    else dir.y = 1;


   // cout << dir.x << "   " << dir.y << endl;




}

