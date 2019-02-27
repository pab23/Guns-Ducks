#include "../include/Player.h"


/** CLASE PLAYER
    *@desc Esta clase implementa el objeto Jugador que se inicializa en los valores por defecto y pasandole por parametro la referencia a la textura del jugador.
    * move(int, int) Mueve el jugador en la direccion indicada por parametro.
    * getters y setters necesarios


    *@author Pablo Amoros Becerra Javier Ramirez de la Cal

*/
Player::Player(Texture &tex)
{
        spr = new Sprite(tex);
        spr->setOrigin(84/2,76/2);
        spr->setTextureRect(IntRect(0*84, 0*76, 84, 76));
        spr->setPosition(400,300);

        /*box = new RectangleShape({75,75/4});
        box->setFillColor(Color::Red);
        box->setOrigin(75/2,75/8);
        box->setPosition(400,305+(75/4));*/

        box = new RectangleShape({84,76/4});
        box->setFillColor(Color::Blue);
        box->setOrigin(84/2,76/2);
        box->setPosition(400,300+76/1.8);

        speed = 2; dir = {1, 0};
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

    dir = {x, y};
    spr->move(speedX, speedY);
    box->move(speedX, speedY);


}


Sprite Player::getSprite()
{
    return *spr;
}
RectangleShape Player::getRect()
{
    return *box;
}
Vector2f Player::getPosition()
{
    return spr->getPosition();
}
Vector2i Player::getDir()
{
    return dir;
}

FloatRect Player::getBounds(){
    return spr->getGlobalBounds();
}

FloatRect Player::getBoundsBox(){
    return box->getGlobalBounds();
}



