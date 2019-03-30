#include "../include/Blood.h"
#include "Blood.h"

Blood::Blood(Texture &tex)
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

    estado = false;

    /// spr de cadaver de pato ///
    spr_pato = new Sprite(tex);
    spr_pato->setTextureRect(IntRect(RandomNumber(0,4)*aux, 120, aux, aux));
    spr_pato->setOrigin(aux/2, aux/2);
    spr_pato->setScale(1.5,1.5);
    //spr_pato->setRotation(RandomNumber(0,360));//Doy una rotacion aleatoria
}

void Blood::setPosition(Vector2f vec)
{
    spr->setPosition(vec.x,vec.y);
    spr_pato->setPosition(vec.x,vec.y);
}

void Blood::activar(){estado = true;}
bool Blood::getEstado(){return estado;}

Sprite Blood::getSprite(){return *spr;}
Sprite Blood::getSprite_pato(){return *spr_pato;}
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
