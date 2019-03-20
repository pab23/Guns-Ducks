#include "../include/Game.h"
#include <typeinfo>
#include<iostream>


/** CLASE PLAYER
    *@desc Clase principal en la que se ejecuta el juego, en ella se crea la ventana y se inicializan todas las variables necesarias para el funcionamiento del juego.
    * gameLoop() flujo principal de ejecucion del bucle del juego.
    * listenKeyboard() se tratan las pulsaciones de las teclas y se realizan las acciones aisgnadas a cada una de ellas.
    * draw() Se limpia la pantalla y posteriormente se dibujan todos los elementos que deben aparecer.
    * colisiones() Se tratan las colisiones con enemigos y paredes.

    *Añadidos las zonas de curación y la barra de vida (al disparar enemigos te baja la vida, y las zonas curan cada 1s)

    *@author Sergio Bañuls Martínez

*/

Game::Game(Vector2i win_dim)
{
    winDim=win_dim;
    win = new RenderWindow(VideoMode(win_dim.x, win_dim.y), "Guns & Ducks");
    win->setFramerateLimit(60);


    tex_player = new Texture();
    tex_player->loadFromFile("resources/sprites.png");
    player = new Player(*tex_player);




    for( unsigned i = 0; i < 12; i++)
    {
        Enemy aux(*tex_player);
        enemigos.push_back(aux);
    }

    font = new Font();
    font->loadFromFile("letra_pixel.ttf");
    txt_time = new Text("0",*font);
    txt_time->setPosition(10,10);

    //zona
    life_zone = new RectangleShape({100,100});
    life_zone->setFillColor(Color::Green);
    life_zone->setPosition({100, 300});

    //zona
    bad_zone = new RectangleShape({100,100});
    bad_zone->setFillColor(Color::Red);
    bad_zone->setPosition({500, 300});

    //OBJETOS
    tex_object = new Texture();
    tex_object->loadFromFile("resources/objetos.png");
    for(unsigned i = 0; i < 4; i++)
    {
        string type="botijola";
        string type2="ducknamyte";
        string type3="planchadito";
        string type4="pato";

        Object* aux4 = new Object(type4, *tex_object);
        objetos.push_back(aux4);

        Object* aux3 = new Object(type3, *tex_object);
        objetos.push_back(aux3);

        Object* aux2 = new Object(type2, *tex_object);
        objetos.push_back(aux2);

        Object* aux = new Object(type, *tex_object);
        objetos.push_back(aux);
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
        zone_timer = zone_clock.getElapsedTime();
        if(zone_timer.asSeconds() >= 1)
        {
            inZona();
            inBad();
            zone_clock.restart();
        }

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

    win->draw(*life_zone);
    win->draw(*bad_zone);
    win->draw(player->getSprite());

    for(unsigned i = 0; i < enemigos.size(); i++)
        win->draw(enemigos[i].getSprite());


    for( unsigned j = 0; j < balas.size(); j++)
        win->draw(balas[j].getSprite());

    for( unsigned j = 0; j < objetos.size(); j++)
        win->draw(objetos[j]->getSprite());


    timeToString();
    win->draw(*txt_time);
    win->draw(player->getScoreTxt());
    win->draw(player->getLifeBox());
    win->draw(player->getLifeTxt());
    win->draw(player->getShieldBox());
    win->draw(player->getShieldTxt());


    win->display();
}

void Game::colisiones()
{
    FloatRect barrier0x({0,-30}, {winDim.x,1});
    FloatRect barrierxx({0,winDim.y+30}, {winDim.x,1});
    FloatRect barrieryy({winDim.x+30,0}, {1,winDim.y});
    FloatRect barrier0y({-30,0}, {1,winDim.y});

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
                player->setScore(player->getScore()+kEnemy_reward);
                player->gestionaVida(-10);
            }
        }

    }
    for(int i = 0; i < objetos.size(); i++)
    {
        if(objetos[i]->getBounds().intersects(player->getSprite().getGlobalBounds()))
        {


            if(objetos[i]->getTipo()=="b")
            {
                cout<<"Botijola: recuperamos todo el escudo"<<endl;
                player->setShield(100-player->getShield());
            }
            else if(objetos[i]->getTipo()=="d")
            {
                cout<<"Ducknamyte: elimina a todos los enemigos"<<endl;
                player->setShield(30);
            }
            else if(objetos[i]->getTipo()=="p")
            {
                cout<<"Planchadito: Recuperamos toda la vida"<<endl;
                player->setLife(100-player->getLife());
            }
            else if(objetos[i]->getTipo()=="m")
            {
                cout<<"Modo PaTo: matas a todos de un tiro"<<endl;
                player->setShield(20);
            }
            objetos.erase(objetos.begin()+i);

        }
    }

}

void Game::timeToString()
{
    float val = general_clock.getElapsedTime().asSeconds();

    stringstream ss;
    ss << val;

    txt_time->setString(ss.str());
}

void Game::inZona()
{

    if(player->getSprite().getGlobalBounds().intersects(life_zone->getGlobalBounds()))
    {
        player->setLife(10);
        cout<<player->getLife()<<endl;
    }
}
void Game::inBad()
{

    if(player->getSprite().getGlobalBounds().intersects(bad_zone->getGlobalBounds()))
    {
        player->setLife(-10);
        cout<<player->getLife()<<endl;
    }
}



