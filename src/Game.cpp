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
    srand(time(NULL));
    winDim=win_dim;
    win = new RenderWindow(VideoMode(win_dim.x, win_dim.y), "Guns & Ducks");
    win->setFramerateLimit(60);


    loadTextures();//Cargamos texturas


    /// mapa de prueba
    spr_map = new Sprite(*tex_map);
    spr_map->setPosition(0,0);
    spr_map->setScale(1.1,1.1);

    /// HUD
    hud = new Hud(*tex_ammo);


    ///valores del game
    cont_oleadas = 0, cont_rondas = 0, cont_bajas = 0;

    ///player
    player = new Player(*tex_player);

    ///enemy
    enemy_clock.restart();
    cont_oleadas = 0;//contador de oleadas

    /// info del juego
    primer = true;
    info = false;

    font = new Font();
    font->loadFromFile("letra_pixel.ttf");
    txt_time = new Text("0",*font);
    txt_time->setPosition(10,10);

    ///zona
    life_zone = new RectangleShape({100,100});
    life_zone->setFillColor(Color::Green);
    life_zone->setPosition({100, 300});

    /// Object

    /*for(unsigned i = 0; i < 4; i++)
    {
        objetos.push_back(new Object("botijola", *tex_object));
        objetos.push_back(new Object("ducknamyte", *tex_object));
        objetos.push_back(new Object("planchadito", *tex_object));
        objetos.push_back(new Object("pato", *tex_object));
        objetos.push_back(new Object("municionCarabina", *tex_object));
        objetos.push_back(new Object("municionEscopeta", *tex_object));
    }*/

    modoPato=false;

    gameLoop();

}

void Game::loadTextures(){
    //player
    tex_player = new Texture();
    tex_player->loadFromFile("resources/player.png");


    //enemy
    tex_enemy = new Texture();
    tex_enemy->loadFromFile("resources/patos.png");


    //blood

    tex_bloods = new Texture();
    tex_bloods->loadFromFile("resources/bloods-tex.png");

    //mapa de prueba

    tex_map = new Texture();
    tex_map->loadFromFile("resources/mapa.png");

    //object
     tex_object = new Texture;
    tex_object->loadFromFile("resources/objetos.png");

    // ammo display
    tex_ammo = new Texture;
    tex_ammo->loadFromFile("resources/ammo-display.png");




}
void Game::gameLoop()
{

    while(win->isOpen())
    {
        update();

          ///Animation
        if(animation_timer.asSeconds() >= .2)
        {
            //Player
            player->changePos(player->getDir(), 1, player->getPosition());
            player->setSpr(player->getAnim().getSprite());
            //Enemigos
            for(unsigned i = 0; i < enemigos.size(); i++)
            {
                enemigos[i].changePos(enemigos[i].getDir(), 0, enemigos[i].getPosition());
                enemigos[i].setSpr(enemigos[i].getAnim().getSprite());
            }

            animation_clock.restart();
        }

        if(zone_timer.asSeconds() >= 1)
        {
            inZona();
            zone_clock.restart();
        }


        /** T_OLEADAS, N_OLEADAS y N_ENEMIES_OLEADA se definen en game.h
            Nº ENEMIGOS A CREAR = valor por defecto (5) + nº de oleadas que se han creado hasta el momento
            Ejemplo: Oleada 1 = 5 + 0; Oleada 2 = 5 + 1; Oleada 3 = 5 + 2; Oleada 4 = 5 + 3;      **/

        if(enemy_timer.asSeconds() > T_OLEADAS && cont_oleadas < N_OLEADAS ){//Nueva oleada

            int n = N_ENEMIES_OLEADA + cont_oleadas;
            float s = SPEED_ENEMY + ((float)cont_rondas/10);
            //cout << "Ronda " << cont_rondas << ". Velocidad de enemigo: " << s <<". Enemigos creados: " << n << endl;
            crearEnemy(n,s);//crea x enemigos y hace cont_oleadas++
            enemy_clock.restart();
            }
        else if(cont_oleadas == N_OLEADAS && enemigos.size()==0 && cont_rondas < N_RONDAS ){//Nueva ronda
            for(unsigned i = 0; i< bloods.size();i++)
            {
               //Quito cadaveres, cambio el color de la sangre
               bloods[i].setStateBlood(2);
               bloods[i].setStateDuck(0);

            }
            //Reinicio el crono de enemigos y las oleadas
            enemy_clock.restart();
            cont_oleadas=0;
            cont_rondas++;
        }

        ///Modo Pato///
        modoPato_timer=modoPato_clock.getElapsedTime();
        if(modoPato && modoPato_timer.asSeconds()>=15)
        {
            cout<<"Se acabo el modo pato"<<endl;
            modoPatoOFF();
        }



        draw();

    }
}
void Game::update()
{
    enemy_timer = enemy_clock.getElapsedTime();
    bullet_cooldown = bullet_clock.getElapsedTime();
    listenKeyboard();
    moverEnemigos();
    colisiones();
    playerCollisions();
    zone_timer = zone_clock.getElapsedTime();
    animation_timer = animation_clock.getElapsedTime();
}
void Game::draw()
{

    win->clear(Color::White);

    win->draw(*spr_map);

     /// BLOOD ///

    for(unsigned i = 0; i< bloods.size();i++)
    {
        if(bloods[i].getStateBlood() == 1 || bloods[i].getStateBlood() == 2) win->draw(bloods[i].getSpriteBlood());// 0 = invisible; 1 = visible; 3 = vieja (la sangre se ve con menos color)
        if(bloods[i].getStateDuck() == 1)  win->draw(bloods[i].getSpriteDuck());// 0 = invisible; 1 = visible

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
        win->draw(balas[j]->getSprite());

    //////////////////////////////////////////////////////////////////////////
    for(unsigned i=0; i<enemigos.size(); i++)
    {


        if(player->getPosition().y>enemigos[i].getPosition().y) //Cuando el player esta por encima del enemigo las box enemigas son rojas
        {
            enemigos[i].setColor(0);
            win->draw(enemigos[i].getSprite());
            if(info)
                win->draw(enemigos[i].getRect());

        }

    }
    win->draw(player->getSprite());
    if(info)
        win->draw(player->getRect());

    for(unsigned i=0; i<enemigos.size(); i++)
    {
        if(player->getPosition().y<=enemigos[i].getPosition().y)
        {
            enemigos[i].setColor(1);
            win->draw(enemigos[i].getSprite());
            if(info)
                win->draw(enemigos[i].getRect());
        }
    }


    //////////////////////////////////////////////////////////////////////////

    timeToString();
    win->draw(*txt_time);
    win->draw(player->getScoreTxt());
    win->draw(player->getLifeBox());
    win->draw(player->getLifeTxt());
    win->draw(player->getShieldBox());
    win->draw(player->getShieldTxt());

    /// OBJECT ///

    for( unsigned j = 0; j < objetos.size(); j++)
        win->draw(objetos[j]->getSprite());


    /// HUD (AMMO DISPLAY, RONDAS, ETC

    hud->drawHud(win);
    hud->setTxtAmmo(player->getArmaActiva().getMunicion());


    win->display();
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
          if(e.type == Event::KeyPressed && e.key.code == Keyboard::C)
        {
            player->cambiarArma();
            hud->setGun(player->getArmaActiva().getNombre());

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


  if( Keyboard::isKeyPressed(Keyboard::Space))
    {
        if(player->getArmaActiva().getNombre()=="Pistola" && bullet_cooldown.asSeconds() >= .5f)
        {
            bullet_clock.restart();
            balas.push_back(new Bullet(player->getPosition(), player->getDir(), 5));//ultimo parametro radio a falta de implementar diferentes tipos de bala
            //cout<<player->getArmaActiva().getNombre()<<": "<<player->getArmaActiva().getMunicion()<<endl;

        }
        if(player->getArmaActiva().getNombre()=="Carabina" && bullet_cooldown.asSeconds() >= .2f)
        {
            if(player->getArmaActiva().getMunicion()>0)
            {
                bullet_clock.restart();
                balas.push_back(new Bullet(player->getPosition(), player->getDir(), 3));//ultimo parametro radio a falta de implementar diferentes tipos de bala
                player->quitarBalaActiva();
            }
            else{
                    //cout<<player->getArmaActiva().getNombre()<<": SIN MUNICION"<<endl;
                    player->cambiarArma();
                    hud->setGun(player->getArmaActiva().getNombre());//cambiar arma en el hud del ammo
            }

        }
         if(player->getArmaActiva().getNombre()=="Escopeta" && bullet_cooldown.asSeconds() >= .9f)
        {
             if(player->getArmaActiva().getMunicion()>0)
             {
                 bullet_clock.restart();
                 balas.push_back(new Bullet(player->getPosition(), player->getDir(), 7));//ultimo parametro radio a falta de implementar diferentes tipos de bala
                 player->quitarBalaActiva();
                //cout<<player->getArmaActiva().getNombre()<<": "<<player->getArmaActiva().getMunicion()<<endl;
             }
             else{
                   // cout<<player->getArmaActiva().getNombre()<<": SIN MUNICION"<<endl;
                   player->cambiarArma();
                   hud->setGun(player->getArmaActiva().getNombre());//cambiar arma en el hud del ammo
             }
        }
    }

    for(unsigned i=0; i<balas.size(); i++)
        balas[i]->move();

}
void Game::colisiones()
{

    for(unsigned i=0; i<balas.size(); i++)
    {
        Vector2f aux = balas[i]->getPos();
        if(aux.x < 0 || aux.x > winDim.x || aux.y < 0 || aux.y > winDim.y)
        {
            borrarBala(i);
        }
    }

     for(unsigned i = 0; i < balas.size();i++)
    {
        for(unsigned j = 0; j < enemigos.size();j++)
        {
            if(balas[i]->getBounds().intersects(enemigos[j].getBounds()))
            {
                borrarBala(i);

                enemigos[j].setVida(player->getArmaActiva().getNombre());
                if(enemigos[j].getVida() <= 0)
                {
                    posicionarBlood(enemigos[j].getPosition());
                    objRandom(enemigos[j].getPosition());//activa y posiciona una sangre en la posicion del enemigo muerto. Falta el if(enemymuerto) para activarla solo cuando muera
                    enemigos.erase(enemigos.begin()+j);
                    cont_bajas++;
                    hud->setTxtDuckdead(cont_bajas);
                    player->setScore(player->getScore()+ENEMY_REWARD);


                }



                break;
            }
        }
    }
    itemCollisions();

}


///MODO PATO///
void Game::modoPatoON()
{
    modoPato_clock.restart();
    for(unsigned i=0; i<enemigos.size();i++)
    {
        enemigos[i].setHp(1);
    }
    modoPato=true;
}
void Game::modoPatoOFF()
{
    for(unsigned i=0; i<enemigos.size(); i++)
    {
        enemigos[i].setHp(100);
    }
    modoPato=false;
}
    /// ENEMIES ///

void Game::crearEnemy(int n, float s){

/// Creo un enemigo y lo meto en el array de enemigos. Con cada enemigo creo tambien una de sangre y la meto en su correspondiente array de bloods. Ej: 15 enemigos 15 blood

 for( unsigned i = 0; i < n; i++)
    {

        Enemy aux(*tex_enemy,s, (int)100);
        enemigos.push_back(aux);
        crearBlood();
    }
    cont_oleadas++;


}
void Game::moverEnemigos(){

    /** EXPLICACION METODO moverEnemigos():

    -Este metodo recorre el array de enemigos donde se encuentran todos los enemigos creados por el momento.
    -La posicion de cada enemigo (y player) viene representada por un vector2f.
    -Creo un array v_vectores, donde en su primera casilla meto la pos del player y en el resto meto solo la pos de los enemigos que esten a "x" distancia del enemigo actual que estoy recorriendo en el array.
    -Es decir, si esa "x" distancia es menor que una distancia minima establecida en Enemy.h, se considera que "esta demasiado cerca" e introduzco la posicion del enemigo proximo en el array v_vectores.
    -Una vez tengo en v_vectores la posicion del player y los enemigos que estan cerca del enemigo actual selleccionado, llamo al metodo .move() para calcular el vector de direccion
    que tiene que seguir el enemigo teniendo en cuenta la posicion del player y las del resto de enemigos cercanos, para que cada enemigo siga al jugador y no colisionen entre ellos (se repelen).
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
    bloods.push_back(Blood(*tex_bloods));

}
void Game::posicionarBlood(Vector2f pos){
    /// Recorro el array de sangres, la primera que no este activada (posicionada) la activo y la posiciono en la pos del enemigo
    for(unsigned i = 0; i < bloods.size(); i++)
    {
        if(bloods[i].getStateBlood() == 0){
            bloods[i].setPosition(pos);
            bloods[i].setStateBlood(1);
            bloods[i].setStateDuck(1);
            break;
        }

    }
}



void Game::inZona()
{

    if(player->getSprite().getGlobalBounds().intersects(life_zone->getGlobalBounds()))
    {
        player->setLife(10);
        //cout<<player->getLife()<<endl;
    }
}

void Game::playerCollisions()
{
    for(unsigned i = 0; i < enemigos.size(); i++)
    {
        if(enemigos[i].getBounds().intersects(player->getBounds()))
        {
            if(enemigos[i].getPosition().x > player->getPosition().x)
            {
                player->empujon(-1,0);
            }
            else
            {
                player->empujon(1,0);
            }
            if(enemigos[i].getPosition().y > player->getPosition().y)
            {
                player->empujon(0, -1);
            }
            else
            {
                player->empujon(0, 1);
            }
            player->gestionaVida(-10);
            //break;
        }
    }

}
void Game::borrarBala(int i)
{

    Bullet* aux = balas[i];
    balas.erase(balas.begin()+i);
    delete aux;

}
void Game::itemCollisions()
{
    for(int i = 0; i < objetos.size(); i++)
    {
        if(objetos[i]->getBounds().intersects(player->getSprite().getGlobalBounds()))
        {
            string aux = objetos[i]->getTipo();

            if(aux=="b")
            {
                //cout<<"Botijola: recuperamos todo el escudo"<<endl;
                player->setShield(100-player->getShield());
            }
            else if(aux=="d")
            {
                //cout<<"Ducknamyte: elimina a todos los enemigos"<<endl;
                for(unsigned i = 0; i < enemigos.size(); i++)
                {
                posicionarBlood(enemigos[i].getPosition());//activa y posiciona una sangre en la posicion del enemigo muerto. Falta el if(enemymuerto) para activarla solo cuando muera
                cont_bajas++;

                }
                hud->setTxtDuckdead(cont_bajas);
                enemigos.erase(enemigos.begin(), enemigos.begin()+enemigos.size());
            }
            else if(aux=="p")
            {
                //cout<<"Planchadito: Recuperamos toda la vida"<<endl;
                player->setLife(100-player->getLife());
            }
            else if(aux=="m")
            {
                //cout<<"Modo PaTo: matas a todos de un tiro"<<endl;
                //player->getSprite().setColor(Color::Red);
            }
            else if(aux=="ammoC")
            {
                player->cogerMunicion("Carabina", 50);

            }

            else if(aux=="ammoE")
            {
                player->cogerMunicion("Escopeta", 10);

            }
            Object* obau = objetos[i];
            objetos.erase(objetos.begin()+i);
            delete obau;

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

void Game::objRandom(Vector2f pos)
{
    string ob_aux[] = {"botijola", "ducknamyte", "planchadito", "pato", "municionCarabina", "municionEscopeta"};
    int num = floor(1+rand()%(10-1));
    if(num == 1)
    {
        int type = floor(rand()%(6-1));
        objetos.push_back(new Object(ob_aux[type], *tex_object, pos));
    }
}

