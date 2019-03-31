#include "../include/Enemy.h"
#include <math.h>
Enemy::Enemy(Texture &tex, float vel)
{

    Vector2i ventana(800,600);
    Vector2f pos = this->getRandomPosition(ventana);
    speed = vel;
    spr = new Sprite(tex);
    spr->setOrigin(24/2,24/2);
    spr->setTextureRect(IntRect(0*75, 0*75, 24, 24));
    spr->setPosition(pos);
    spr->scale(1.5,1.5);
    dir ={0,1};

    box = new RectangleShape({spr->getTextureRect().width,spr->getTextureRect().height/4});
    box->setFillColor(Color::Red);
    box->setOrigin(box->getSize().x/2,box->getSize().y/2);
    box->setPosition(getPosition().x,getPosition().y+spr->getTextureRect().height/3);

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
FloatRect Enemy::getBoundsBox(){
    return box->getGlobalBounds();
}
Vector2f Enemy::getPosition(){
    return spr->getPosition();
}
void Enemy::setColor(int color)
{
    if(color == 0)
    box->setFillColor(Color::Green);
    else
    box->setFillColor(Color::Red);
}

Vector2i Enemy::getDir()
{
    return dir;
}
RectangleShape Enemy::getRect()
{
    return *box;
}
void Enemy::setPosition(float x, float y){
    spr->setPosition(x,y);
    box->setPosition(x,y+spr->getTextureRect().height/3);
}
void Enemy::setPosition(Vector2f vec){
    spr->setPosition(vec.x,vec.y);
    box->setPosition(vec.x,vec.y+spr->getTextureRect().height/3);
}
void Enemy::move(Vector2f playerPosition, bool collision){

    direction = playerPosition - getPosition();
    normalizedDir.x = direction.x / (sqrt(pow(direction.x, 2) + pow(direction.y, 2)));
    normalizedDir.y = direction.y / (sqrt(pow(direction.x, 2) + pow(direction.y, 2)));
    Vector2f currentSpeed = normalizedDir * speed;//distancia por velocidad



    //Creamos un vector auxiliar
    Vector2f aux_direction,aux_normalizedDir, aux_currentSpeed;

    aux_direction= Vector2f(playerPosition.x  + RandomNumber(5,100), playerPosition.y + RandomNumber(5,100)) - getPosition();
    aux_normalizedDir.x = aux_direction.x / (sqrt(pow(aux_direction.x, 2) + pow(aux_direction.y, 2)));
    aux_normalizedDir.y = aux_direction.y / (sqrt(pow(aux_direction.x, 2) + pow(aux_direction.y, 2)));
    aux_currentSpeed = aux_normalizedDir * speed;//distancia por velocidad

    if(collision)
        spr->move(aux_currentSpeed);
    else
    spr->move(currentSpeed);

    box->move(currentSpeed);

    float phi= atan((playerPosition.y - getPosition().y)/(playerPosition.x - getPosition().x));

    if(playerPosition.x - getPosition().x < 0 && playerPosition.x - getPosition().y<0)
        phi= phi + M_PI;
    //cout << phi <<endl;

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


    //cout << normalizedDir.x << "   " << normalizedDir.y << endl;
     //cout << direction.x << "   " << direction.y << endl;



}
int Enemy::RandomNumber( int inicio, int fin ){


     /*
      Genera un número aleatorio entre
      inicio y fin.
     */

     int resultado = 0;

     // Calculamos el margen entre inicio y fin
     int margen = fin - inicio;

     // Establecemos el comienzo del intervalo
     int comienzo = inicio;

     // Comprobamos si el intervalo está al revés
     if( inicio > fin ){

      // Cambiamos el comienzo
      comienzo = fin;

      // Cambiamos el signo de la diferencia
      margen = margen * -1;
     }

     /*
      * Añadimos uno al margen ya que la función
      * rand calcula entre el 0 y uno menos que
      * el margen.
      */
     margen++;

     /*
      Si el intervalo no comienza y acaba en el
      mismo número.
     */

     // Generamos el número aleatorio.
     resultado = comienzo + (rand() % margen);

     return resultado;
}
Vector2f Enemy::getRandomPosition(Vector2i ventana){

    int vx = ventana.x; int vy = ventana.y;

    //Establecemos de que pared sale. 1=left, 2=down, 3=right,4=up
    int a = RandomNumber(1,4);
    int posx,posy;
    switch(a)
    {
        case 1: posx =-100;
                posy = RandomNumber(0,vy);
        break;

        case 2: posy=vy+100;
                posx = RandomNumber(0,vx);
        break;

        case 3: posx= vx +100;
                posy=RandomNumber(0,vy);
        break;

        case 4: posy= -100;
                posx = RandomNumber(0,vx);
        break;

    }
    return Vector2f(posx,posy);
}


