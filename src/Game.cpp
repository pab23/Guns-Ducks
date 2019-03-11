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

    win = new RenderWindow(VideoMode(win_dim.x, win_dim.y), "Guns & Ducks");
    win->setFramerateLimit(60);


    //aqui marcamos el zoom que queremos general
    view.reset(sf::FloatRect(0,0,win_dim.x, win_dim.y));




//Vector2f position(win_dim.x/2, win_dim.y/2);
    textura1 = new Texture;
    sprite1 = new Sprite;

    textura1->loadFromFile("resources/mapaAlfa.png");


    tex_player = new Texture();
    tex_player->loadFromFile("resources/sprites.png");
    player = new Player(*tex_player);




    for( unsigned i = 0; i < 10; i++)
    {
        Enemy aux(*tex_player);
        enemigos.push_back(aux);
    }



    gameLoop();

}

void Game::gameLoop()
{
    while(win->isOpen())
    {
        bullet_cooldown = bullet_clock.getElapsedTime();
        listenKeyboard();

        colisiones();

        //pasamos ahora por parametro las dimensiones
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
        }

    }
    if( Keyboard::isKeyPressed(Keyboard::W))
    {
        //if(player->getPosition().y > 0)
            y = -1;
    }
    else if( Keyboard::isKeyPressed(Keyboard::S))
    {
        //if(player->getPosition().y < winDim.y)
            y = 1;
    }
    if( Keyboard::isKeyPressed(Keyboard::A))
    {
        //if(player->getPosition().x > 0)
            x = -1;
    }
    else if( Keyboard::isKeyPressed(Keyboard::D))
    {
        //if(player->getPosition().x < winDim.x)
        x = 1;
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

    //Camara al centro
    view.setCenter(player->getPosition());
    win->setView(view);
    cout<<"x: "<<player->getPosition().x<<" y: "<<player->getPosition().y<<endl;

    win->draw(player->getSprite());

    for(unsigned i = 0; i < enemigos.size(); i++)
        win->draw(enemigos[i].getSprite());


    for( unsigned j = 0; j < balas.size(); j++)
        win->draw(balas[j].getSprite());



    win->display();
}

void Game::colisiones()
{
    FloatRect barrier0x({0,-30}, {win->getSize().x,1});
    FloatRect barrierxx({0,win->getSize().y+30}, {win->getSize().x,1});
    FloatRect barrieryy({win->getSize().x+30,0}, {1,win->getSize().y});
    FloatRect barrier0y({-30,0}, {1,win->getSize().y});

    /*for(unsigned i=0; i<balas.size(); i++)
    {

        if(balas[i].getBounds().intersects(barrier0x))
            balas.erase(balas.begin()+i);

        if(balas[i].getBounds().intersects(barrier0y))
            balas.erase(balas.begin()+i);

        if(balas[i].getBounds().intersects(barrierxx))
            balas.erase(balas.begin()+i);

        if(balas[i].getBounds().intersects(barrieryy))
            balas.erase(balas.begin()+i);


    }*/

     for(int i = 0; i < balas.size();i++)
        {

            for(int j = 0; j < enemigos.size();j++)
            {
                if(balas[i].getBounds().intersects(enemigos[j].getBounds()))
                {
                    balas.erase(balas.begin()+i);
                    enemigos.erase(enemigos.begin()+j);
                }
            }

        }





}

