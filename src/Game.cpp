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

    tex_enemy = new Texture();
    tex_enemy->loadFromFile("resources/patos.png");

    enemy_clock.restart();

    primer = true;
    info = false;

    font = new Font();
    font->loadFromFile("letra_pixel.ttf");
    txt_time = new Text("0",*font);
    txt_time->setPosition(10,10);

    //zona
    life_zone = new RectangleShape({100,100});
    life_zone->setFillColor(Color::Green);
    life_zone->setPosition({100, 300});


    gameLoop();

}

void Game::gameLoop()
{

    while(win->isOpen())
    {
        enemy_timer = enemy_clock.getElapsedTime();
        bullet_cooldown = bullet_clock.getElapsedTime();
        listenKeyboard();
        moverEnemigos();
        colisiones();
        zone_timer = zone_clock.getElapsedTime();
        if(zone_timer.asSeconds() >= 1)
        {
            inZona();
            zone_clock.restart();
        }

        draw();

        if(enemy_timer.asSeconds() > 5.0 ){

            crearEnemy();
            enemy_clock.restart();
            }

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

    win->draw(player->getSprite());
     win->draw(player->getCircle());
      win->draw(*life_zone);
    win->draw(player->getSprite());

    for(unsigned i = 0; i < enemigos.size(); i++)
        win->draw(enemigos[i].getSprite());



    for( unsigned j = 0; j < balas.size(); j++)
        win->draw(balas[j].getSprite());

    colisionBox();
     timeToString();
    win->draw(*txt_time);
    win->draw(player->getScoreTxt());
    win->draw(player->getLifeBox());
    win->draw(player->getLifeTxt());
    win->draw(player->getShieldBox());
    win->draw(player->getShieldTxt());


    win->display();
}

void Game::moverEnemigos(){

   for(unsigned k = 0; k < enemigos.size(); k++){
        if(!enemigos[k].getBounds().intersects(player->getCircle().getGlobalBounds()))
            enemigos[k].move(player->getPosition(), false);//Necesita la pos del player para moverse hacia el
        }

         //collision
    for(int i=0;i<enemigos.size();i++)
    for(int j=0;j<enemigos.size();j++)
    {

        if(enemigos[i].getBounds().intersects(enemigos[j].getBounds()) && enemigos[i].getPosition() != enemigos[j].getPosition())
        {
            //enemigos[i].move(player->getPosition(), true);
            //enemigos[j].move(player->getPosition(), false);
            float ix = enemigos[i].getPosition().x;
            float iy = enemigos[i].getPosition().y;
            float jx = enemigos[j].getPosition().x;
            float jy = enemigos[j].getPosition().y;

            if(ix > jx){
            enemigos[i].setPosition(ix+1,iy);
            enemigos[j].setPosition(jx-1,jy);
            }else if(ix < jx){
            enemigos[i].setPosition(ix-1,iy);
            enemigos[j].setPosition(jx+1,jy);
            }

            if(iy > jy){
            enemigos[i].setPosition(ix,iy+1);
            enemigos[j].setPosition(jx,jy-1);
            }else if(iy < jy){
            enemigos[i].setPosition(ix,iy-1);
            enemigos[j].setPosition(jx,jy+1);
            }

            //cout << "chocamos" <<endl;
        }
    }



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
                    player->setScore(player->getScore()+kEnemy_reward);
                    player->gestionaVida(-10);
                    break;
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

    /*for(unsigned i=0; i<enemigos.size(); i++)
    {

        if(player->getBoundsBox().intersects(enemigos[i].getBoundsBox()))
        {
            if(player->getPosition().y<enemigos[i].getPosition().y)
            {
                player->move(0,-1);

            }

            else if(player->getPosition().y>enemigos[i].getPosition().y)
            {
                player->move(0,1);
            }

            if(player->getPosition().x<enemigos[i].getPosition().x)
            {
                player->move(-1,0);

            }

            else if(player->getPosition().x>enemigos[i].getPosition().x)
            {
                player->move(1,0);
            }
            cout<<"ups"<<endl;



        }
    }*/
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

void Game::crearEnemy(){

 for( unsigned i = 0; i < 15; i++)
    {

        Enemy aux(*tex_enemy,.5);
        enemigos.push_back(aux);
    }


}

void Game::crearAnimaciones(){
  // set up the animations for all four directions (set spritesheet and push frames)

    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(* tex_enemy);
    walkingAnimationDown.addFrame(sf::IntRect(24, 0, 24, 24));
    walkingAnimationDown.addFrame(sf::IntRect(48, 0, 24, 24));
    walkingAnimationDown.addFrame(sf::IntRect(24, 0, 24, 24));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 24, 24));

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(* tex_enemy);
    walkingAnimationLeft.addFrame(sf::IntRect(24, 58, 24, 24));
    walkingAnimationLeft.addFrame(sf::IntRect(48, 58, 24, 24));
    walkingAnimationLeft.addFrame(sf::IntRect(24, 58, 24, 24));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 58, 24, 24));

    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(* tex_enemy);
    walkingAnimationRight.addFrame(sf::IntRect(24, 142, 24, 24));
    walkingAnimationRight.addFrame(sf::IntRect(51, 142, 24, 24));
    walkingAnimationRight.addFrame(sf::IntRect(24, 142, 24, 24));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 142, 24, 24));

    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(* tex_enemy);
    walkingAnimationUp.addFrame(sf::IntRect(24, 30, 24, 24));
    walkingAnimationUp.addFrame(sf::IntRect(48, 30, 24, 24));
    walkingAnimationUp.addFrame(sf::IntRect(24, 30, 24, 24));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 30, 24, 24));

    Animation walkingAnimationUpLeft;
    walkingAnimationUpLeft.setSpriteSheet(* tex_enemy);
    walkingAnimationUpLeft.addFrame(sf::IntRect(28, 116, 24, 24));
    walkingAnimationUpLeft.addFrame(sf::IntRect(51, 116, 24, 24));
    walkingAnimationUpLeft.addFrame(sf::IntRect(28, 116, 24, 24));
    walkingAnimationUpLeft.addFrame(sf::IntRect( 4, 116, 24, 24));

    Animation walkingAnimationUpRight;
    walkingAnimationUpRight.setSpriteSheet(* tex_enemy);
    walkingAnimationUpRight.addFrame(sf::IntRect(28, 200, 24, 24));
    walkingAnimationUpRight.addFrame(sf::IntRect(50, 200, 24, 24));
    walkingAnimationUpRight.addFrame(sf::IntRect(28, 200, 24, 24));
    walkingAnimationUpRight.addFrame(sf::IntRect( 4, 200, 24, 24));

    Animation walkingAnimationDownLeft;
    walkingAnimationDownLeft.setSpriteSheet(* tex_enemy);
    walkingAnimationDownLeft.addFrame(sf::IntRect(24, 86, 24, 24));
    walkingAnimationDownLeft.addFrame(sf::IntRect(52, 86, 24, 24));
    walkingAnimationDownLeft.addFrame(sf::IntRect(24, 86, 24, 24));
    walkingAnimationDownLeft.addFrame(sf::IntRect( 0, 86, 24, 24));

    Animation walkingAnimationDownRight;
    walkingAnimationDownRight.setSpriteSheet(* tex_enemy);
    walkingAnimationDownRight.addFrame(sf::IntRect(24, 170, 24, 24));
    walkingAnimationDownRight.addFrame(sf::IntRect(48, 170, 24, 24));
    walkingAnimationDownRight.addFrame(sf::IntRect(24, 170, 24, 24));
    walkingAnimationDownRight.addFrame(sf::IntRect( 0, 170, 24, 24));

    Animation* currentAnimation = &walkingAnimationDown;

    // set up AnimatedSprite
    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite.setPosition(sf::Vector2f(winDim / 2));

   // sf::Clock frameClock;
    //float speed = 80.f;
    //bool noKeyWasPressed = true;
    }
