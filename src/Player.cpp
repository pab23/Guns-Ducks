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
        box = new RectangleShape({spr->getTextureRect().width,spr->getTextureRect().height/4});
        box->setFillColor(Color::Blue);
        box->setOrigin(box->getSize().x/2,box->getSize().y/2);
        box->setPosition(getPosition().x,getPosition().y+spr->getTextureRect().height/3);
        circle = new CircleShape();
        circle->setOrigin(50,50);
        circle->setPosition(400,300);
        circle->setRadius(50);
        circle->setFillColor(Color(255,0,0,120));
        spr->setOrigin(75/2,75/2);
        spr->setTextureRect(IntRect(1*75, 0*75, 75, 75));
        spr->setPosition(400,300);
        spr->scale(.5,.5);

        speed = 4; dir = {1, 0};
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
    circle->move(speedX, speedY);
    box->move(speedX, speedY);


}

Sprite Player::getSprite()
{
    return *spr;
}
CircleShape Player::getCircle(){return *circle;}
Vector2f Player::getPosition()
{
    return spr->getPosition();
}
Vector2i Player::getDir()
{
    return dir;
}
RectangleShape Player::getRect()
{
    return *box;
}

FloatRect Player::getBounds(){
    return spr->getGlobalBounds();
}

FloatRect Player::getBoundsBox(){
    return box->getGlobalBounds();
}

void Player::setPosition(Vector2f vec){
    spr->setPosition(vec);
    box->setPosition(vec.x, vec.y);
}
/*void Player::cambiarAnimacion(){
   int x,y;
   x = getDir().x;
   y = getDir().y;

   //if(x == 0 && y == 1)


}*/




