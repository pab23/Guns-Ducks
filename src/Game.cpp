#include "../include/Game.h"


/** CLASE PLAYER
    *@desc Clase principal en la que se ejecuta el juego, en ella se crea la ventana y se inicializan todas las variables necesarias para el funcionamiento del juego.
    * gameLoop() flujo principal de ejecucion del bucle del juego.
    * listenKeyboard() se tratan las pulsaciones de las teclas y se realizan las acciones aisgnadas a cada una de ellas.
    * draw() Se limpia la pantalla y posteriormente se dibujan todos los elementos que deben aparecer.
    * colisiones() Se tratan las colisiones con enemigos y paredes.


    *@author Pablo Amoros Becerra Javier Ramirez de la Cal

*/

Game::Game(Vector2i win_dim)
{
    winDim=win_dim;
    win = new RenderWindow(VideoMode(win_dim.x, win_dim.y), "Guns & Ducks");
    win->setFramerateLimit(60);

    tex_player = new Texture();
    tex_player->loadFromFile("resources/sprites.png");
    player = new Player(*tex_player);
    info = false;

    for( unsigned i = 0; i < 10; i++)
    {
        Enemy aux(*tex_player);
        enemigos.push_back(aux);
    }

    primer = true;

    gameLoop();

}

void Game::gameLoop()
{
    while(win->isOpen())
    {
        bullet_cooldown = bullet_clock.getElapsedTime();
        listenKeyboard();

        colisiones();

        draw();

    }
}

void Game::listenKeyboard()
{
    int x = 0, y = 0;
    while(win->pollEvent(e))
    {
        if(e.type == Event::Closed || (e.type == Event::KeyPressed && (e.key.code == Keyboard::Escape)))
        {
            win->close();
            cout<<"Bala: "<<balas.size()<<endl;
            for( unsigned i = 0; i < balas.size(); i++)
                cout<<balas[i].getSprite().getPosition().x<<" "<<balas[i].getSprite().getPosition().y<<endl;
        }
        if(e.type == Event::KeyPressed && e.key.code == Keyboard::I)
        {
            info = !info;
        }

    }
    if( Keyboard::isKeyPressed(Keyboard::W))
    {
        if(player->getPosition().y > 0)y = -1;
    }
    else if( Keyboard::isKeyPressed(Keyboard::S))
    {
        if(player->getPosition().y < winDim.y)y = 1;
    }
    if( Keyboard::isKeyPressed(Keyboard::A))
    {
        if(player->getPosition().x > 0)x = -1;
    }
    else if( Keyboard::isKeyPressed(Keyboard::D))
    {
        if(player->getPosition().x < winDim.x)x = 1;
    }
    if(x!=0 || y!=0)
        player->move(x, y);


    if( Keyboard::isKeyPressed(Keyboard::Space) && bullet_cooldown.asSeconds() >= .2f)
    {
        bullet_clock.restart();
        balas.push_back(Bullet(player->getPosition(), player->getDir(), 5));//ultimo parametro radio a falta de implementar diferentes tipos de bala
    }


    for(unsigned i=0; i<balas.size(); i++)
        balas[i].move();

}

void Game::draw()
{

    win->clear();






    for( unsigned j = 0; j < balas.size(); j++)
        win->draw(balas[j].getSprite());

    colisionBox();



    win->display();
}

void Game::colisiones()
{
    FloatRect barrier0x({-30,-30}, {winDim.x+60 , 1});
    FloatRect barrierxx({-30 , winDim.y+30}, {winDim.x+60 , 1});
    FloatRect barrieryy({winDim.x+30 , -30}, {1 , winDim.y+60});
    FloatRect barrier0y({-30 , -30}, {1 , winDim.y+60});

    for(unsigned i=0; i<balas.size(); i++)
    {

        if(balas[i].getBounds().intersects(barrier0x))
            balas.erase(balas.begin()+i);

        if(balas[i].getBounds().intersects(barrier0y))
            balas.erase(balas.begin()+i);

        if(balas[i].getBounds().intersects(barrierxx))
            balas.erase(balas.begin()+i);

        if(balas[i].getBounds().intersects(barrieryy))
            balas.erase(balas.begin()+i);


    }

     for(unsigned i = 0; i < balas.size();i++)
        {

            for(unsigned j = 0; j < enemigos.size();j++)
            {
                if(balas[i].getBounds().intersects(enemigos[j].getBounds()))
                {
                    balas.erase(balas.begin()+i);
                    enemigos.erase(enemigos.begin()+j);
                }
            }

        }





}

void Game::colisionBox()
{


    if(enemigos.size() == 0)
    {
        win->draw(player->getSprite());
        if(info)
            win->draw(player->getRect());
    }
    for(unsigned i=0; i<enemigos.size(); i++)
    {


        if(player->getPosition().y-enemigos[i].getPosition().y < 0) //Cuando el player esta por encima del enemigo las box enemigas son rojas
            enemigos[i].setColor(0);
        else
            enemigos[i].setColor(1); //Cuando el player esta por debajo las box son verdes

        win->draw(enemigos[i].getSprite());
        win->draw(player->getSprite());
        if(info)
        {
            win->draw(enemigos[i].getRect());
            win->draw(player->getRect());
        }

    }

    for(unsigned i=0; i<enemigos.size(); i++)
    {
        if(player->getPosition().y-enemigos[i].getPosition().y < 0)
        {
            win->draw(enemigos[i].getSprite());
            if(info)
                win->draw(enemigos[i].getRect());
        }
    }
}

