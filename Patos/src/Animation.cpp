
#include "../include/Animation.h"

Animation::Animation(Texture tex, int obj)
{
    //obj indica si es player o enemy:  0 - enemy   1 - player
    anim_tex = tex;
    pos = 0;
    col = 0;
    Sprite *aux = new Sprite(anim_tex);
    Vector2i ventana(800,600);
    Vector2f posi = this->getRandomPosition(ventana);
    if(obj == 0)//enemy
    {
        aux->setOrigin(0,0);
        aux->setTextureRect(IntRect(24,30,24,24));
        aux->setPosition(posi);
        //uu
        matrix[0][0] = *aux;
        aux->setTextureRect(IntRect(48,30,24,24));
        matrix[1][0] = *aux;
        aux->setTextureRect(IntRect(48,30,24,24));
        matrix[2][0] = *aux;
        aux->setTextureRect(IntRect(24,30,24,24));
        matrix[3][0] = *aux;
        aux->setTextureRect(IntRect(0,30,24,24));
        //ur
        matrix[0][1] = *aux;
        aux->setTextureRect(IntRect(28,200,24,24));
        matrix[1][1] = *aux;
        aux->setTextureRect(IntRect(50,200,24,24));
        matrix[2][1] = *aux;
        aux->setTextureRect(IntRect(28,200,24,24));
        matrix[3][1] = *aux;
        aux->setTextureRect(IntRect(4,200,24,24));
        //rr
        matrix[0][2] = *aux;
        aux->setTextureRect(IntRect(24,142,24,24));
        matrix[1][2] = *aux;
        aux->setTextureRect(IntRect(51,142,24,24));
        matrix[2][2] = *aux;
        aux->setTextureRect(IntRect(24,142,24,24));
        matrix[3][2] = *aux;
        aux->setTextureRect(IntRect(0,142,24,24));
        //rd
        matrix[0][3] = *aux;
        aux->setTextureRect(IntRect(24,170,24,24));
        matrix[1][3] = *aux;
        aux->setTextureRect(IntRect(48,170,24,24));
        matrix[2][3] = *aux;
        aux->setTextureRect(IntRect(24,170,24,24));
        matrix[3][3] = *aux;
        aux->setTextureRect(IntRect(0,170,24,24));
        //dd
        matrix[0][4] = *aux;
        aux->setTextureRect(IntRect(24,170,24,24));
        matrix[1][4] = *aux;
        aux->setTextureRect(IntRect(48,170,24,24));
        matrix[2][4] = *aux;
        aux->setTextureRect(IntRect(24,170,24,24));
        matrix[3][4] = *aux;
        aux->setTextureRect(IntRect(0,170,24,24));
        //dl
        matrix[0][5] = *aux;
        aux->setTextureRect(IntRect(24,86,24,24));
        matrix[1][5] = *aux;
        aux->setTextureRect(IntRect(52,86,24,24));
        matrix[2][5] = *aux;
        aux->setTextureRect(IntRect(24,86,24,24));
        matrix[3][5] = *aux;
        aux->setTextureRect(IntRect(0,86,24,24));
        //ll
        matrix[0][6] = *aux;
        aux->setTextureRect(IntRect(24,58,24,24));
        matrix[1][6] = *aux;
        aux->setTextureRect(IntRect(48,58,24,24));
        matrix[2][6] = *aux;
        aux->setTextureRect(IntRect(24,58,24,24));
        matrix[3][6] = *aux;
        aux->setTextureRect(IntRect(0,58,24,24));
        //lu
        matrix[0][7] = *aux;
        aux->setTextureRect(IntRect(28,116,24,24));
        matrix[1][7] = *aux;
        aux->setTextureRect(IntRect(51,116,24,24));
        matrix[2][7] = *aux;
        aux->setTextureRect(IntRect(28,116,24,24));
        matrix[3][7] = *aux;
        aux->setTextureRect(IntRect(4,116,24,24));

        spr = new Sprite(matrix[pos][col]);

    }else if(obj == 1)//player
    {

    }

}
FloatRect Animation::getBounds()
{
    return spr->getGlobalBounds();
}
int Animation::RandomNumber( int inicio, int fin ){


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
Vector2f Animation::getRandomPosition(Vector2i ventana){

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

Vector2f Animation::getPosition(){
    return spr->getPosition();
}


void Animation::setPosition(float x, float y)
{
    cout<<"Pos = " << x << "/"<<y<<endl;
    spr->setPosition(x,y);
}
void Animation::setPosition(Vector2f vec)
{
    cout<<"Pos = " << vec.x << "/"<<vec.y<<endl;
    spr->setPosition(vec.x,vec.y);
}

Sprite Animation::getSprite()
    {
        return *spr;
    }

void Animation::changePos()
{
    if(pos == 3)//Esta en la ultima fila
    {
        pos = 0;
    }else
    {
        pos = pos+1;
    }
    spr = new Sprite(matrix[pos][col]);
}

void Animation::changeSprite(int sprit, int obj)
{
    //sprit dice que columna de la matriz utilizamos, y obj si es del player o del enemy
    //u = up r = right  d = down  l = left
    //0-uu 1-ur 2-rr 3-rd 4-dd 5-dl 6-ll 7-lu

    if(obj == 0) //enemy
    {
        col = sprit;
        switch(sprit)
        {
            case 0:
                spr = new Sprite(matrix[pos][col]);
            break;

            case 1:
                spr = new Sprite(matrix[pos][col]);
            break;

            case 2:
                spr = new Sprite(matrix[pos][col]);
            break;

            case 3:
                spr = new Sprite(matrix[pos][col]);
            break;

            case 4:
               spr = new Sprite(matrix[pos][col]);
            break;

            case 5:
                spr = new Sprite(matrix[pos][col]);
            break;

            case 6:
                spr = new Sprite(matrix[pos][col]);
            break;

            case 7:
                spr = new Sprite(matrix[pos][col]);
            break;

        }


    }else if (obj == 1)// player
    {
        col = sprit;
        switch(sprit)
        {
            case 0:
              spr = new Sprite(matrix[pos][col]);
            break;

            case 1:
               spr = new Sprite(matrix[pos][col]);
            break;

            case 2:
                spr = new Sprite(matrix[pos][col]);
            break;

            case 3:
                spr = new Sprite(matrix[pos][col]);
            break;

            case 4:
                spr = new Sprite(matrix[pos][col]);
            break;

            case 5:
               spr = new Sprite(matrix[pos][col]);
            break;

            case 6:
               spr = new Sprite(matrix[pos][col]);
            break;

            case 7:
                spr = new Sprite(matrix[pos][col]);
            break;

        }

    }

}
