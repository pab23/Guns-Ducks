#include "../include/Game.h"


Game::Game(Vector2i win_dim)
{
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

        listenKeyboard();



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
    player->move(x, y);
}

void Game::draw()
{

    win->clear();

    win->draw(player->getSprite());
    for(unsigned i = 0; i < enemigos.size(); i++)
        win->draw(enemigos[i].getSprite());

    win->display();
}

