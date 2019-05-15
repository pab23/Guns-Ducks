
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
    int medida_sprite;
    float padding;
    if(obj == 0)//enemy
    {
         aux->setOrigin(12,12);
        aux->setTextureRect(IntRect(24,30,24,24));
        aux->setPosition(posi);
        aux->setScale(1.5,1.5);
        //uu

        aux->setTextureRect(IntRect(48,30,24,24));
        matrix[0][0] = *aux;
        aux->setTextureRect(IntRect(24,30,24,24));
        matrix[1][0] = *aux;
        aux->setTextureRect(IntRect(48,30,24,24));
        matrix[2][0] = *aux;
        aux->setTextureRect(IntRect(0,30,24,24));
        matrix[3][0] = *aux;
        //ur

        aux->setTextureRect(IntRect(28,200,24,24));
        matrix[0][1] = *aux;
        aux->setTextureRect(IntRect(50,200,24,24));
        matrix[1][1] = *aux;
        aux->setTextureRect(IntRect(28,200,24,24));
        matrix[2][1] = *aux;
        aux->setTextureRect(IntRect(4,200,24,24));
        matrix[3][1] = *aux;
        //rr

        aux->setTextureRect(IntRect(24,142,24,24));
        matrix[0][2] = *aux;
        aux->setTextureRect(IntRect(51,142,24,24));
        matrix[1][2] = *aux;
        aux->setTextureRect(IntRect(24,142,24,24));
        matrix[2][2] = *aux;
        aux->setTextureRect(IntRect(0,142,24,24));
        matrix[3][2] = *aux;
        //rd

        aux->setTextureRect(IntRect(24,170,24,24));
        matrix[0][3] = *aux;
        aux->setTextureRect(IntRect(48,170,24,24));
        matrix[1][3] = *aux;
        aux->setTextureRect(IntRect(24,170,24,24));
        matrix[2][3] = *aux;
        aux->setTextureRect(IntRect(0,170,24,24));
        matrix[3][3] = *aux;
        //dd

        aux->setTextureRect(IntRect(24,0,24,24));
        matrix[0][4] = *aux;
        aux->setTextureRect(IntRect(48,0,24,24));
        matrix[1][4] = *aux;
        aux->setTextureRect(IntRect(24,0,24,24));
        matrix[2][4] = *aux;
        aux->setTextureRect(IntRect(0,0,24,24));
        matrix[3][4] = *aux;
        //dl

        aux->setTextureRect(IntRect(24,86,24,24));
        matrix[0][5] = *aux;
        aux->setTextureRect(IntRect(52,86,24,24));
        matrix[1][5] = *aux;
        aux->setTextureRect(IntRect(24,86,24,24));
        matrix[2][5] = *aux;
        aux->setTextureRect(IntRect(0,86,24,24));
        matrix[3][5] = *aux;
        //ll

        aux->setTextureRect(IntRect(24,58,24,24));
        matrix[0][6] = *aux;
        aux->setTextureRect(IntRect(48,58,24,24));
        matrix[1][6] = *aux;
        aux->setTextureRect(IntRect(24,58,24,24));
        matrix[2][6] = *aux;
        aux->setTextureRect(IntRect(0,58,24,24));
        matrix[3][6] = *aux;
        //lu

        aux->setTextureRect(IntRect(28,116,24,24));
        matrix[0][7] = *aux;
        aux->setTextureRect(IntRect(51,116,24,24));
        matrix[1][7] = *aux;
        aux->setTextureRect(IntRect(28,116,24,24));
        matrix[2][7] = *aux;
        aux->setTextureRect(IntRect(4,116,24,24));
        matrix[3][7] = *aux;

        spr = new Sprite(matrix[pos][col]);


    }else if(obj == 1)//player
    {
        medida_sprite = 32;
        padding = 1;
        aux->setOrigin(16,16);
        aux->setTextureRect(IntRect(0,32,32,32));
        aux->setPosition(400,300);
        aux->setScale(1.5,1.5);
        //uu

        aux->setTextureRect(IntRect(2,169,32,32));
        matrix[0][0] = *aux;
        aux->setTextureRect(IntRect(34,169,32,32));
        matrix[1][0] = *aux;
        aux->setTextureRect(IntRect(66,169,32,32));
        matrix[2][0] = *aux;
        aux->setTextureRect(IntRect(98,169,32,32));
        matrix[3][0] = *aux;
        //ur

        aux->setTextureRect(IntRect(2,237,32,32));
        matrix[0][1] = *aux;
        aux->setTextureRect(IntRect(34,237,32,32));
        matrix[1][1] = *aux;
        aux->setTextureRect(IntRect(66,237,32,32));
        matrix[2][1] = *aux;
        aux->setTextureRect(IntRect(98,237,32,32));
        matrix[3][1] = *aux;
        //rr


        aux->setTextureRect(IntRect(2,137,32,32));
        matrix[0][2] = *aux;
        aux->setTextureRect(IntRect(34,137,32,32));
        matrix[1][2] = *aux;
        aux->setTextureRect(IntRect(66,137,32,32));
        matrix[2][2] = *aux;
        aux->setTextureRect(IntRect(98,137,32,32));
        matrix[3][2] = *aux;
        //rd

        aux->setTextureRect(IntRect(2,69,32,32));
        matrix[0][3] = *aux;
        aux->setTextureRect(IntRect(34,69,32,32));
        matrix[1][3] = *aux;
        aux->setTextureRect(IntRect(66,69,32,32));
        matrix[2][3] = *aux;
        aux->setTextureRect(IntRect(98,69,32,32));
        matrix[3][3] = *aux;
        //dd

        aux->setTextureRect(IntRect(2,1,32,32));
        matrix[0][4] = *aux;
        aux->setTextureRect(IntRect(34,1,32,32));
        matrix[1][4] = *aux;
        aux->setTextureRect(IntRect(66,1,32,32));
        matrix[2][4] = *aux;
        aux->setTextureRect(IntRect(98,1,32,32));
        matrix[3][4] = *aux;
        //dl

        aux->setTextureRect(IntRect(1,35,32,32));
        matrix[0][5] = *aux;
        aux->setTextureRect(IntRect(33,35,32,32));
        matrix[1][5] = *aux;
        aux->setTextureRect(IntRect(65,35,32,32));
        matrix[2][5] = *aux;
        aux->setTextureRect(IntRect(97,35,32,32));
        matrix[3][5] = *aux;
        //ll

        aux->setTextureRect(IntRect(1,101,32,32));
        matrix[0][6] = *aux;
        aux->setTextureRect(IntRect(33,101,32,32));
        matrix[1][6] = *aux;
        aux->setTextureRect(IntRect(65,101,32,32));
        matrix[2][6] = *aux;
        aux->setTextureRect(IntRect(97,101,32,32));
        matrix[3][6] = *aux;
        //lu

        aux->setTextureRect(IntRect(1,203,32,32));
        matrix[0][7] = *aux;
        aux->setTextureRect(IntRect(33,203,32,32));
        matrix[1][7] = *aux;
        aux->setTextureRect(IntRect(65,203,32,32));
        matrix[2][7] = *aux;
        aux->setTextureRect(IntRect(97,203,32,32));
        matrix[3][7] = *aux;

        spr = new Sprite(matrix[pos][col]);

    }


}

Animation::~Animation()
{
    delete spr;

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




Sprite Animation::getSprite()
    {
        return *spr;
    }

void Animation::changePos(Vector2i dire, int obj, Vector2f posi)
{

    if(dire != dir)//si ha cambiado de direccion
    {
        dir = dire;

        if(dire.x == 0)
        {
            if(dire.y == -1)
            {
                changeSprite(0, obj, posi);
            }else if(dire.y == 1)
            {
                changeSprite(4, obj, posi);
            }
        }else if(dire.x == 1)
        {
            if(dire.y == -1)
            {
                changeSprite(1, obj, posi);
            }else if(dire.y == 0)
            {
                changeSprite(2, obj, posi);
            }else if(dire.y == 1)
            {
                changeSprite(3, obj, posi);
            }
        }else if(dire.x == -1)
        {
            if(dire.y == -1)
            {
                changeSprite(7, obj, posi);
            }else if(dire.y == 0)
            {
                changeSprite(6, obj, posi);
            }else if(dire.y == 1)
            {
                changeSprite(5, obj, posi);
            }
        }

    }else//si no ha cambiado de direccion
    {

        if(pos == 3)//Esta en la ultima fila
        {
            pos = 0;
        }else
        {
            pos = pos+1;
        }

        spr = new Sprite(matrix[pos][col]);
        spr->setPosition(posi);

    }

}

void Animation::changeSprite(int sprit, int obj, Vector2f posi)
{
    //sprit dice que columna de la matriz utilizamos, y obj si es del player o del enemy
    //u = up r = right  d = down  l = left
    //0-uu 1-ur 2-rr 3-rd 4-dd 5-dl 6-ll 7-lu

    if(obj == 0) //enemy
    {
        col = sprit;
        spr = new Sprite(matrix[pos][col]);

    }else if (obj == 1)// player
    {
        col = sprit;
        spr = new Sprite(matrix[pos][col]);

    }

    spr->setPosition(posi);


}

