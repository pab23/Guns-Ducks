#include "../include/Player.h"



Player::Player(Texture &tex)
{
        spr = new Sprite(tex);
        box = new RectangleShape();
        box->setSize({50, 20});
        spr->setOrigin(75/2,75/2);
        spr->setTextureRect(IntRect(1*75, 0*75, 75, 75));
        spr->setPosition(0,0);

        speed = 5; dir = {1, 0};
}

Sprite Player::getSprite()
{
    return *spr;
}

Vector2f Player::getPosition()
{
    return spr->getPosition();
}

void Player::move(int x, int y)
{
    float speedX;
    float speedY;

    switch(x)
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
    switch(y)
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
    spr->move(speedX, speedY);

    dir = {speedX, speedY};
}



