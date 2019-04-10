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

        armaActiva=0;
        armas.push_back(Gun("Pistola", 1));


        spr->setOrigin(75/2,75/2);
        spr->setTextureRect(IntRect(1*75, 0*75, 75, 75));
        spr->setPosition(400,300);
        spr->scale(.5,.5);

        //Score
        font_txt = new Font();
        font_txt->loadFromFile("letra_pixel.ttf");
        txt_score = new Text("0",*font_txt);
        txt_score->setPosition(10, 40);
        txt_score->setColor(Color::Yellow);

        //Life
        life = 100;
        life_box = new RectangleShape({200, 10});
        life_box->setPosition(0, 590);
        life_box->setFillColor(Color::Green);
        txt_life = new Text("100", *font_txt, 10);
        txt_life->setPosition(life_box->getSize().x/2,590);
        txt_life->setColor(Color::Black);

        //shield
        shield = 100;
        shield_box = new RectangleShape({200, 10});
        shield_box->setPosition(0, 570);
        shield_box->setFillColor(Color::Blue);
        txt_shield = new Text("100", *font_txt, 10);
        txt_shield->setPosition(shield_box->getSize().x/2,570);
        txt_shield->setColor(Color::Black);

        box = new RectangleShape({spr->getScale().x*spr->getTextureRect().width,spr->getScale().y*spr->getTextureRect().height/4});
        box->setFillColor(Color::Blue);
        box->setOrigin(box->getSize().x/2,box->getSize().y/2);
        box->setPosition(getPosition().x+3,getPosition().y+spr->getTextureRect().height/3);

        /*circle = new CircleShape();
        circle->setOrigin(50,50);
        circle->setPosition(spr->getPosition().x+2,spr->getPosition().y );
        circle->setRadius(50);
        circle->setFillColor(Color(255,0,0,120));*/
        anim = new Animation(tex,1);

        speed = 2.5; dir = {1, 0};
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
    //circle->move(speedX, speedY);
    box->move(speedX, speedY);


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

int Player::getLife()
{
    return life;
}
RectangleShape Player::getLifeBox()
{
    return *life_box;
}
int Player::getShield()
{
    return shield;
}
RectangleShape Player::getShieldBox()
{
    return *shield_box;
}


void Player::setLife(int x)
{

    if(x < 0)//Si resta
    {
        if((life+x) > 0)
        {
            life += x;
            Vector2f nuevo({life_box->getSize().x+2*x, life_box->getSize().y});
            life_box->setSize(nuevo);

            std::stringstream ss;
            ss << life;
            txt_life->setString(ss.str());
            txt_life->setPosition(life_box->getSize().x/2,txt_life->getPosition().y);
        }
        else
        {
            life = 0;
            Vector2f nuevo({0, life_box->getSize().y});
            life_box->setSize(nuevo);
            txt_life->setString("0");
            txt_life->setPosition(life_box->getSize().x/2,txt_life->getPosition().y);
        }
    }
    else//Si suma
    {
        if(life + x <= 100)
        {
            life += x;
            Vector2f nuevo({life_box->getSize().x+2*x, life_box->getSize().y});
            life_box->setSize(nuevo);

            std::stringstream ss;
            ss << life;
            txt_life->setString(ss.str());
            txt_life->setPosition(life_box->getSize().x/2,txt_life->getPosition().y);
        }
    }


    if (life >= 50)
    {
        life_box->setFillColor(Color::Green);
    }else if (life < 50 && life >= 20)
    {
        life_box->setFillColor(Color(255, 102, 0));
    }else
    {
        life_box->setFillColor(Color::Red);
    }


}
Text Player::getLifeTxt()
{
    return *txt_life;
}
Text Player::getShieldTxt()
{
    return *txt_shield;
}

void Player::gestionaVida(int x)
{
    if(shield > 0)
        this->setShield(x);
    else
        this->setLife(x);
}

void Player::setShield(int x)
{

    if(x < 0)//Si resta
    {
        if((shield+x) > 0)
        {
            shield += x;
            Vector2f nuevo({shield_box->getSize().x+2*x, shield_box->getSize().y});
            shield_box->setSize(nuevo);

            std::stringstream ss;
            ss << shield;
            txt_shield->setString(ss.str());
            txt_shield->setPosition(shield_box->getSize().x/2,txt_shield->getPosition().y);
        }
        else
        {
            shield = 0;
            Vector2f nuevo({0, shield_box->getSize().y});
            shield_box->setSize(nuevo);
            txt_shield->setString("0");
            txt_shield->setPosition(shield_box->getSize().x/2,txt_shield->getPosition().y);
        }
    }
    else//Si suma
    {
        if(shield + x <= 100)
        {
            shield += x;
            Vector2f nuevo({shield_box->getSize().x+2*x, shield_box->getSize().y});
            shield_box->setSize(nuevo);

            std::stringstream ss;
            ss << shield;
            txt_shield->setString(ss.str());
            txt_shield->setPosition(shield_box->getSize().x/2,txt_shield->getPosition().y);
        }
    }


    if (life >= 50)
    {
        life_box->setFillColor(Color::Green);
    }else if (life < 50 && life >= 20)
    {
        life_box->setFillColor(Color(255, 102, 0));
    }else
    {
        life_box->setFillColor(Color::Red);
    }


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



string Player::infoArmaActiva(int i)
{
    stringstream ss;
    ss<<"Selecionada "<<armas[i].getNombre()<<": "<<armas[i].getMunicion();
    string s=ss.str();
    return s;
}

Gun Player::getArmaActiva()
{
    return armas[armaActiva];
}

void Player::cambiarArma()
{
    if(armaActiva==armas.size()-1)
        armaActiva=0;
    else
        armaActiva++;
    //cout<<armas[armaActiva].getNombre()<<": "<<armas[armaActiva].getMunicion()<<endl;
    //cout<<infoArmaActiva(armaActiva)<<endl;
}

void Player::cogerMunicion(string n, int nbalas)
{
    bool estar=false;
    int indice=0;

    for(int i=0; i<armas.size() && !estar; i++) //Si el arma ya esta en el inventario solo le añadimos municion
    {
        if(armas[i].getNombre()==n)
        {
            estar=true;
            armas[i].setMunicion(nbalas);
            //cout<<armas[i].getNombre()<<": +"<<nbalas<<"balas"<<endl;
        }
    }

    if(!estar) //Si no, la añadimos al inventario
    {
        armas.push_back(Gun(n, nbalas));
        //cout<<"Has cogido: "<<n<<endl;
    }
}

void Player::quitarBalaActiva()
{
    armas[armaActiva].setMunicion(-1);
}
void Player::changePos(Vector2i dire, int obj, Vector2f posi)
{
    anim->changePos(dire, obj, posi);
}
void Player::setSpr(const Sprite &sprit)
{
    spr = new Sprite(sprit);
}
Animation Player::getAnim()
{
    return *anim;
}
void Player::empujon(int dirX, int dirY)
{
    float speedEm = 5, speedX, speedY;
    switch(dirX)
    {
        case 1:
            speedX = speedEm;
        break;
        case -1:
            speedX = -speedEm;
        break;
        default:
            speedX = 0;
        break;
    }
    switch(dirY)
    {
        case 1:
            speedY = speedEm;
        break;
        case -1:
            speedY = -speedEm;
        break;
        default:
            speedY = 0;
        break;
    }
    spr->move(speedX, speedY);
    box->move(speedX, speedY);
}

