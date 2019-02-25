#include "../include/Game.h"


Game::Game(Vector2i win_dim)
{
    winDim=win_dim;
    win = new RenderWindow(VideoMode(win_dim.x, win_dim.y), "Guns & Ducks");
    win->setFramerateLimit(60);

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

        draw();

    }
}

void Game::listenKeyboard()
{
    int x = 0, y = 0;
    while(win->pollEvent(e))
    {
        if(e.type == Event::Closed)
            win->close();
    }
    if( Keyboard::isKeyPressed(Keyboard::W))
    {
        y = -1;
    }
    else if( Keyboard::isKeyPressed(Keyboard::S))
    {
        y = 1;
    }
    if( Keyboard::isKeyPressed(Keyboard::A))
    {
        x = -1;
    }
    else if( Keyboard::isKeyPressed(Keyboard::D))
    {
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

    win->draw(player->getSprite());

    for(unsigned i = 0; i < enemigos.size(); i++)
        win->draw(enemigos[i].getSprite());


    for( unsigned j = 0; j < balas.size(); j++)
        win->draw(balas[j].getSprite());




    win->display();
}

void Game::colisiones()
{
    FloatRect barrier0x({0,-30}, {winDim.x,1});
    FloatRect barrierxx({0,winDim.x+30}, {winDim.x,1});
    FloatRect barrier0y({winDim.x+30,0}, {1,winDim.y});
    FloatRect barrieryy({-30,0}, {1,winDim.y});

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

