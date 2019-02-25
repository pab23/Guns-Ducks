#include "Game.h"



Game::Game(Vector2i win_dim)
{
    win = new RenderWindow(VideoMode(win_dim.x, win_dim.y), "Guns & Ducks");
    tex_player = new Texture();
    tex_player->loadFromFile("resources/sprites.png");
    player = new Player(*tex_player);


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
    while(win->pollEvent(*e))
    {
        if(e->type == Event::Closed)
            win->close();
    }
}

void Game::draw()
{
    win->clear();

    win->draw(player->getSprite());

    win->display();
}

