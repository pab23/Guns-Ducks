#include "Player.h"



Player::Player(Texture &tex)
{
        spr = new Sprite(tex);
        box.setSize({50, 20});
        spr->setOrigin(75/2,75/2);
        spr->setTextureRect(IntRect(1*75, 0*75, 75, 75));
        spr->setPosition(0,0);
}

Sprite Player::getSprite()
{
    return *spr;
}

