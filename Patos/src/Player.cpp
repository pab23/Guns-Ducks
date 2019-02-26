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
        box = new RectangleShape();
        box->setSize({50, 20});
        spr->setOrigin(75/2,75/2);
        spr->setTextureRect(IntRect(1*75, 0*75, 75, 75));
        spr->setPosition(400,300);

        font_txt = new Font();
        font_txt->loadFromFile("letra_pixel.ttf");
        txt_score = new Text("0",*font_txt);
        txt_score->setPosition(10, 40);
        txt_score->setColor(Color::Yellow);
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


}

Sprite Player::getSprite()
{
    return *spr;
}

Vector2f Player::getPosition()
{
    return spr->getPosition();
}
Vector2i Player::getDir()
{
    return dir;
}

int Player::getScore()
{
    return score;
}
Text Player::getScoreTxt()
{
    return *txt_score;
}
void Player::setScore(int x)
{
    score = x;
    std::stringstream ss;
    ss << x;
    txt_score->setString(ss.str());
}






