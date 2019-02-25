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

    //Creamos la zona verde
    verde = new RectangleShape({100,100});
    verde->setFillColor(Color::Blue);
    verde->setPosition(400, 300);
    //Creamos sprite barra de vida
    life_bar = new RectangleShape({200,10});
    life_bar->setFillColor(Color::Green);
    life_bar->setPosition(10, 550);

    gameLoop();

}

void Game::gameLoop()
{
    while(win->isOpen())
    {
        bullet_cooldown = bullet_clock.getElapsedTime();
        zona_cooldown = zona_clock.getElapsedTime();
        if(zona_cooldown.asSeconds() >= 1)
        {
            checkZonaVerde();
            zona_clock.restart();
        }
        listenKeyboard();



        //colisiones();

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
    if( Keyboard::isKeyPressed(Keyboard::Space) && bullet_cooldown.asSeconds() >= .2f)
    {
        bullet_clock.restart();
        balas.push_back(Bullet(player->getPosition(), player->getDir(), 5));//ultimo parametro radio a falta de implementar diferentes tipos de bala
    }

}

void Game::draw()
{

    win->clear();

    win->draw(*verde);
    win->draw(player->getSprite());
    win->draw(*life_bar);


    win->display();
}

void Game::checkZonaVerde()
{
    if (player->getSprite().getGlobalBounds().intersects(verde->getGlobalBounds()))
    {
        player->setLife(player->getLife()-10);
        life_bar->setSize({100, life_bar->getSize().y});//Me quedo aqui la barra no encoge bien
        cout<<player->getLife() <<endl;
    }
}
