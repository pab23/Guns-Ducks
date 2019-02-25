#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include<cmath>﻿



using namespace std;
using namespace sf;

void loadTextures();
string s(double n);
int RandomNumber( int inicio, int fin );
Vector2f getRandomPosition(Vector2f &ventana);


Texture tex_player;
Vector2f vec_windowSize(800,600);//Tamanio de la ventana
const int c_ckp=1; //num de checkpoints
int points[c_ckp][2];


struct Player{
    float x,y,speed,angle;
    Sprite spr_player;

    Player (Texture &tex){
        speed=6;angle=0;
        spr_player.setTexture(tex);
        spr_player.setOrigin(75/2,75/2);
        spr_player.setTextureRect(IntRect(1*75, 0*75, 75, 75));
        spr_player.setPosition(0,0);
    }
    void setPosition(float posx, float posy){
        x = posx;
        y = posy;
        spr_player.setPosition(x,y);
    }
    void setPosition(Vector2f pos){
        x = pos.x;
        y = pos.y;
        spr_player.setPosition(x,y);
    }
    void move(bool Left, bool Down, bool Right,bool Up)
    {

        if(Up){
            y -= speed;
        }
        if(Down){
            y +=  speed;
        }
        if(Right)
        {
            x += speed;
        }
        if(Left)
        {
            x -=  speed;
        }

        setPosition(x,y);
        //spr_player.setRotation(angle*180/3.141593);

    }
    Vector2f getPosition(){return Vector2f(x,y);}

};
struct Enemigo{
    float x,y,speed,angle;
    int n;
    Sprite spr_enemigo;

    Enemigo(Texture &tex){
        x = 0;y=0;speed=5;angle=0;n=0;
        spr_enemigo.setTexture(tex);
        spr_enemigo.setOrigin(75/2,75/2);
        spr_enemigo.setTextureRect(IntRect(0*75, 0*75, 75, 75));
        spr_enemigo.setPosition(0,0);
    }
    void setPosition(float posx, float posy){
        x = posx;
        y = posy;
        spr_enemigo.setPosition(x,y);
    }
    void setPosition(Vector2f pos){
        x = pos.x;
        y = pos.y;
        spr_enemigo.setPosition(x,y);
    }
    void move()
    {
        x += sin(angle) * speed;
        y -= cos(angle) * speed;
        spr_enemigo.setPosition(x,y);
        //spr_enemigo.setRotation(angle*180/3.141593);
    }
    void findTarget()
    {
        float tx=points[n][0];
        float ty=points[n][1];
        float beta = angle-atan2(tx-x,-ty+y);
        if (sin(beta)<0) angle+=0.005*speed; else angle-=0.005*speed;
        if ((x-tx)*(x-tx)+(y-ty)*(y-ty)<25*25) n=(n+1)%c_ckp;
    }

};

int main()
{

    loadTextures();
    srand(time(NULL));//Para el metodo RandomNumber


    Player player(tex_player);
    Vector2f playerPos = Vector2f(400,300);
    player.setPosition(playerPos);

    Enemigo array_enemigos[10](tex_player);


    RenderWindow window(VideoMode(vec_windowSize.x, vec_windowSize.y), "Patos");
    window.setFramerateLimit(60);

    for(int i = 0;i<10;i++){array_enemigos[i].setPosition(getRandomPosition(vec_windowSize));}


    while (window.isOpen())
    {
        window.clear(Color::White);
        window.draw(player.spr_player);
        playerPos = player.getPosition();
        points[0][0] = (playerPos.x,playerPos.y);

        for(int i = 0;i<10;i++){
            window.draw(array_enemigos[i].spr_enemigo);
            if(!array_enemigos[i].spr_enemigo.getGlobalBounds().intersects(player.spr_player.getGlobalBounds())){
                array_enemigos[i].move();
                array_enemigos[i].findTarget();
            }

        }

        bool Up = 0, Right = 0, Down = 0, Left = 0;

            if (Keyboard::isKeyPressed(Keyboard::Up)){ Up=1;}
            if (Keyboard::isKeyPressed(Keyboard::Right)){ Right=1;}
            if (Keyboard::isKeyPressed(Keyboard::Down)){ Down=1;}
            if (Keyboard::isKeyPressed(Keyboard::Left)){ Left=1;}


        player.move(Left,Down,Right,Up);

        if(Up && Right)
        cerr << "Tecla UP y Right" << endl;
        else{
            if(Up)
            cerr << "Tecla up" << endl;
            if(Right)
            cerr << "Tecla right" << endl;
            if(Left)
            cerr << "Tecla left" << endl;
            if(Down)
            cerr << "Tecla down" << endl;
        }

        //Bucle de obtención de evento. Hasta que no se enciende el semaforo
        Event event;
        //while (window.pollEvent(event) && smfVerde && !finish)
        while (window.pollEvent(event))
        {
            switch(event.type){

                case Event::Closed:
                    window.close();
                    break;

                case Event::KeyPressed:
                //Verifico si se pulsa alguna tecla de movimiento.
                    switch(event.key.code) {

                        //Tecla ESC para salir
                        case Keyboard::Q:
                            window.close();
                        break;
                    }
                    break;
            }


        }//END WHILE EVENT



        window.display();
    } //END WHILE WINDOW OPEN

    return 0;
}
void loadTextures(){

    /** ***************** textura *********************************   */

    if (!tex_player.loadFromFile("resources/sprites.png"))
    {
        cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
}
int RandomNumber( int inicio, int fin ){

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
Vector2f getRandomPosition(Vector2f &ventana){

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
