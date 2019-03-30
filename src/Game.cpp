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
    loadTextures();//Cargamos texturas

    //player
    player = new Player(*tex_player);

    //enemy
    enemy_clock.restart();
    enemyRespawn = 0;//contador de oleadas




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

void Game::loadTextures(){
    //player
    tex_player = new Texture();
    tex_player->loadFromFile("resources/sprites.png");


    //enemy
    tex_enemy = new Texture();
    tex_enemy->loadFromFile("resources/patos.png");


    //blood

    tex_bloods = new Texture();
    tex_bloods->loadFromFile("resources/bloods-tex.png");



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

        /**
            T_OLEADAS, N_OLEADAS y N_ENEMIES_OLEADA se definen en game.h
            Nº ENEMIES A CREAR = valor por defecto (5) + nº de oleadas que se han creado hasta el momento
            Ejemplo: Oleada 1 = 5 + 0; Oleada 2 = 5 + 1; Oleada 3 = 5 + 2; Oleada 4 = 5 + 3;

                                                                                                    **/

        if(enemy_timer.asSeconds() > T_OLEADAS && getEnemyRespawn() < N_OLEADAS ){

            int n = N_ENEMIES_OLEADA + getEnemyRespawn();
            crearEnemy(n);//crea x enemigos y hace enemyRespawn++
            enemy_clock.restart();
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

     /// BLOOD ///

    for(unsigned i = 0; i< bloods.size();i++)
    {
        if(bloods[i].getEstado()){//Si estado esta activado(true) se dibuja
             win->draw(bloods[i].getSprite());
             win->draw(bloods[i].getSprite_pato());
             }
    }

    /// PLAYER ///

    win->draw(player->getSprite());
    //win->draw(player->getCircle());

    /// LIFE ZONE ///

    win->draw(*life_zone);


    /// ENEMY ///

    for(unsigned i = 0; i < enemigos.size(); i++){
        win->draw(enemigos[i].getSprite());//Dibuja sprite del enemigo
        if(info)win->draw(enemigos[i].getLinePlayerEnemy(player->getPosition()));//DibuJa la linea entre enemigo y player

        for(int j = 0; j < enemigos.size();j++){
            if(enemigos[i].getPosition() != enemigos[j].getPosition())
               if(info) win->draw(enemigos[i].getLineEnemyEnemy(enemigos[j].getPosition()));//Dibula la linea entre enemigo y enemigo
             }

    }

    /// BULLET ///


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
                    posicionarBlood(enemigos[j].getPosition());//activa y posiciona una sangre en la posicion del enemigo muerto. Falta el if(enemymuerto) para activarla solo cuando muera
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

    /// ENEMIES ///

void Game::crearEnemy(int n){

/// Creo un enemigo y lo meto en el array de enemigos. Con cada enemigo creo tambien una de sangre y la meto en su correspondiente array de bloods. Ej: 15 enemigos 15 blood

 for( unsigned i = 0; i < n; i++)
    {

        Enemy aux(*tex_enemy,.5);
        enemigos.push_back(aux);
        crearBlood();
    }
    enemyRespawn++;


}
int  Game::getEnemyRespawn(){return enemyRespawn;}//nº de oleadas
void Game::moverEnemigos(){

    /** EXPLICACION METODO moverEnemigos():

    -Este metodo recorre el array de enemigos donde se encuentran todos los enemigos creados por el momento.
    -La posicion de cada enemigo (y player) viene representada por un vector2f.
    -Creo un array v_vectores, donde en su primera casilla meto la pos del player y en el resto meto solo la pos de los enemigos que esten a "x" distancia del enemigo actual que estoy recorriendo en el array.
    -Es decir, si esa "x" distancia es menor que una distancia minima establecida en Enemy.h, se considera que "esta demasiado cerca" e introduzco la posicion del enemigo proximo en el array v_vectores.
    -Una vez tengo en v_vectores la posicion del player y los enemigos que estan cerca del enemigo actual selleccionado, llamo al metodo .move() para calcular el vector de direccion
    que tiene que seguir el enemigo teniendo en cuenta la posicion del player y del resto de enemigos cercanos, para que cada enemigo siga al jugador y no colisionen entre ellos (se repelen).
    -Pero esto no evita que, cuando hay muchos enemigos proximos entre si repeliendose, algun sprite se solape con otro. Para evitar esto tambien hago un metodo que cuando interseccionan
    las global-bound de los sprites, empuja +1px a los enemigos teniendo en cuenta cual esta a la der e izq del otro.


    **/

    for(int i=0;i<enemigos.size();i++)
    {
        vector<Vector2f> v_vectores;
        v_vectores.push_back(player->getPosition());//En la primera casilla del vector siempre estara la pos del player
        vector<unsigned> indices = enemigos[i].getEnemyArround(enemigos);//devuelve los indices (del array enemigos) de los enemigos que estan demasiado cerca(< dist_min) respecto al enemigo actual


        if(indices.size() < 1)//este enemigo no esta cerca de ningun otro enemigo
           enemigos[i].move(v_vectores);//se pasa el array con solo una pos, la del player.

        else
        {
            for(unsigned k = 0; k<indices.size();k++)//meto al array de posiciones la pos de los enemigos que estan cerca del enemigo actual
            {   unsigned ind = indices[k];
                v_vectores.push_back(enemigos[ind].getPosition());

            }
            enemigos[i].move(v_vectores);

        }

    }



    /**  Con esto consigo evitar un poco mas que se solapen los sprites **/
    for(int i=0;i<enemigos.size();i++)
    for(int j=0;j<enemigos.size();j++)
    {

        if(enemigos[i].getBounds().intersects(enemigos[j].getBounds()) && enemigos[i].getPosition() != enemigos[j].getPosition())
        {

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

        }
    }



}

    /// BLOOD ///

void Game::crearBlood(){
    Blood blood(*tex_bloods);
    bloods.push_back(blood);

}
void Game::posicionarBlood(Vector2f pos){
    /// Recorro el array de sangres, la primera que no este activada (posicionada) la activo y la posiciono en la pos del enemigo
    for(unsigned i = 0; i < bloods.size(); i++)
    {
        if(!bloods[i].getEstado()){
            bloods[i].setPosition(pos);
            bloods[i].activar();
            break;
        }

    }
}


