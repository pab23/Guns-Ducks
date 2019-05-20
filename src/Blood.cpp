#include "../include/Blood.h"
#include "Blood.h"

Blood::Blood(Texture &tex, string s)
{
    aux = AUX;//variable que es el ancho y alto de cada sprite. De momento es 120px
    spr = new Sprite(tex);
    spr->setTextureRect(IntRect(RandomNumber(0,4)*aux, 0, aux, aux));
    spr->setOrigin(aux/2, aux/2);
    spr->setRotation(RandomNumber(0,360));//Doy una rotacion aleatoria
    spr->setColor(Color::Red);
    // Le asigno una escala aleatoria entre 0.7 y 1.3
    float sizeScale = (float)RandomNumber(0,3)/10;
    if(RandomNumber(0,1) == 1) sizeScale =-sizeScale;//0 positivo 1 negativo
    spr->setScale(1+sizeScale,1+sizeScale);

    state_blood = 0; // 0 = invisible; 1 = visible; 3 = vieja (la sangre se ve con menos color)
    state_duck = 0; // 0 = invisible; 1 = visible

    /// spr de cadaver de pato ///
    spr_duck = new Sprite(tex);
    if(s == "duck")spr_duck->setTextureRect(IntRect(RandomNumber(0,4)*aux, 120, aux, aux));
    else if (s == "dog")spr_duck->setTextureRect(IntRect(RandomNumber(0,4)*aux, 240, aux, aux));
    spr_duck->setOrigin(aux/2, aux/2);
    spr_duck->setScale(1.5,1.5);
    spr_duck->setColor(Color(130,130,130));

}

void Blood::setPosition(Vector2f vec)
{
    spr->setPosition(vec.x,vec.y);
    spr_duck->setPosition(vec.x,vec.y);
}

void Blood::setStateBlood(int s){state_blood = s; if(s == 2)spr->setColor(Color(150,255,255,200)); }
void Blood::setStateDuck(int s){state_duck = s;}
int Blood::getStateBlood(){return state_blood;}
int Blood::getStateDuck(){return state_duck;}
Sprite Blood::getSpriteBlood(){return *spr;}
Sprite Blood::getSpriteDuck(){return *spr_duck;}
int Blood::RandomNumber( int inicio, int fin ){


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

Blood::~Blood()
{
    //dtor
}
