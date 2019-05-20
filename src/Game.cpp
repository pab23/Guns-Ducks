#include "../include/Game.h"


/** CLASE PLAYER
    *@desc Clase principal en la que se ejecuta el juego, en ella se crea la ventana y se inicializan todas las variables necesarias para el funcionamiento del juego.
    * gameLoop() flujo principal de ejecucion del bucle del juego.
    * listenKeyboard() se tratan las pulsaciones de las teclas y se realizan las acciones aisgnadas a cada una de ellas.
    * draw() Se limpia la pantalla y posteriormente se dibujan todos los elementos que deben aparecer.
    * colisiones() Se tratan las colisiones con enemigos y paredes.


    *@author Pablo Amoros Becerra Javier Ramirez de la Cal

*/


Game::Game(RenderWindow &window, int nivel)
{
    srand(time(NULL));
    winDim = Vector2i(window.getSize());

      view.reset(sf::FloatRect(0,0,winDim.x, winDim.y));
      viewHud.reset(sf::FloatRect(0,0,winDim.x, winDim.y));

    win = &window;
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
    player->setMapa(mapa);
    player->setPosition({900, 500});


    ///enemy
    enemy_clock.restart();
    cont_oleadas = 0;//contador de oleadas

    ///mapa

    mapa = new Map();
    mapa->leerMap(nivel);

    ///Sonido

    if(!fondo_buffer.loadFromFile("resources/fondo.wav")){
        cout<<"Error"<<endl;
    }

    fondo_sound.setBuffer(fondo_buffer);
    fondo_sound.setLoop(true);
    fondo_sound.setVolume(35);
    fondo_sound.play();

    if(!pistola_buffer.loadFromFile("resources/pistola.wav")){
        cout<<"Error"<<endl;
    }

    pistola_sound.setBuffer(pistola_buffer);

    if(!carbine_buffer.loadFromFile("resources/lamachina.wav")){
        cout<<"Error"<<endl;
    }

    carbine_sound.setBuffer(carbine_buffer);

    if(!shotgun_buffer.loadFromFile("resources/escupeta.wav")){
        cout<<"Error"<<endl;
    }

    shotgun_sound.setBuffer(shotgun_buffer);

    /// info del juego
    primer = true;
    info = false;
    control_rondas = 0;

    font = new Font();
    font->loadFromFile("resources/letra_pixel.ttf");
    font_zombie = new Font();
    font_zombie->loadFromFile("resources/edosz.ttf");
    txt_time = new Text("0",*font);
    txt_time->setPosition(10,10);
    txt_ronda = new Text("1", *font);
    txt_ronda->setPosition(400,100);
    txt_ronda->setColor(Color::Red);

    txt_objetos = new Text("", *font);
    txt_objetos->setPosition(200,150);


    txt_nrondas = new Text("Ronda 1",*font_zombie);
    txt_nrondas->setCharacterSize(38);
    txt_nrondas->setPosition(600,10);
    txt_nrondas->setColor(Color::Red);

    txt_objetos = new Text("", *font);
    txt_objetos->setPosition(200,150);



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

    //balas
    tex_balas = new Texture();
    tex_balas->loadFromFile("resources/Proyectiles.png");


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

    //PERROS MALIGNOS
    tex_enemy_perro = new Texture();
    tex_enemy_perro->loadFromFile("resources/perros.png");

}
void Game::gameLoop()
{

    while(win->isOpen())
    {

        if(game_clock.getElapsedTime().asMilliseconds() > UPDATE_TIME)
        {
            game_timer_t = game_clock.restart();
            game_timer =float(min(1.f, float(double(game_timer_t.asMilliseconds())/UPDATE_TIME)));
            update();
        }


        draw();

    }
}
void Game::update()
{

    enemy_timer = enemy_clock.getElapsedTime();
    bullet_cooldown = bullet_clock.getElapsedTime();
     listenKeyboard();
    //GameOver
    if(player->getLife() > 0)
    {



    enemy_timer = enemy_clock.getElapsedTime();
    bullet_cooldown = bullet_clock.getElapsedTime();
     listenKeyboard();
    //GameOver
    if(player->getLife() > 0)
    {



    moverEnemigos();
    colisiones();
    playerCollisions();
    colisionMapPlayer(2); //player con agua

    colisionMapPlayer(1); //player con mano
    colisionMapEnemy(1); //enemigo con mano

    colisionMapPlayer(1); //player con mano arbustos y piedras
    colisionMapEnemy(1); //enemigo con mano arbustos y piedras

    zone_timer = zone_clock.getElapsedTime();
    animation_timer = animation_clock.getElapsedTime();


        ///Rondas




        if(control_rondas > 0)
        {
            if(general_clock.getElapsedTime().asSeconds() >= control_rondas+4)
                control_rondas = 0;
        }


        stringstream ss;
        ss<<cont_rondas+1;
        strnr="Ronda "+ss.str();
        txt_nrondas->setString(strnr);


        ///Obj Txt

        if(control_obj > 0)
        {
            if(general_clock.getElapsedTime().asSeconds() >= control_obj+4)
                control_obj = 0;
        }

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
            updateRondaTxt();

        }

        ///Modo Pato///

        modoPato_timer=modoPato_clock.getElapsedTime();

        if(modoPato)
        {
            hud->setModoPato(true);
        }
        else
        {
           hud->setModoPato(false);
        }
        modoPato_timer=modoPato_clock.getElapsedTime();


        if(modoPato && modoPato_timer.asSeconds()>=15)
        {
            cout<<"Se acabo el modo pato"<<endl;
            modoPatoOFF();
        }

    }else{
        cout<<"Muerto"<<endl;
    }



}
}
void Game::draw()
{

    win->clear(Color::White);
      view.setCenter(player->getPosition());
    win->setView(view);
    mapa->draw(win);
    //win->draw(*spr_map);



     /// BLOOD ///

    for(unsigned i = 0; i< bloods.size();i++)
    {
        if(bloods[i].getStateBlood() == 1 || bloods[i].getStateBlood() == 2) win->draw(bloods[i].getSpriteBlood());// 0 = invisible; 1 = visible; 3 = vieja (la sangre se ve con menos color)
        if(bloods[i].getStateDuck() == 1)  win->draw(bloods[i].getSpriteDuck());// 0 = invisible; 1 = visible

    }
    mapa->drawBases(win);
    /// PLAYER ///

    win->draw(player->getSprite());

    //win->draw(player->getCircle());

    /// LIFE ZONE ///

    //win->draw(*life_zone);


    /// ENEMY ///

    for(unsigned i = 0; i < enemigos.size(); i++)
    {
        win->draw(enemigos[i].getSprite());//Dibuja sprite del enemigo
        if(info)win->draw(enemigos[i].getLinePlayerEnemy(player->getPosition()));//DibuJa la linea entre enemigo y player

        for(int j = 0; j < enemigos.size();j++)
        {
            if(enemigos[i].getPosition() != enemigos[j].getPosition())
               if(info) win->draw(enemigos[i].getLineEnemyEnemy(enemigos[j].getPosition()));//Dibula la linea entre enemigo y enemigo
        }

    }

  /// BULLET ///


    for( unsigned j = 0; j < balas.size(); j++)
    {
        win->draw(balas[j]->getSprite());
        if(info)
            win->draw(balas[j]->getBox());
    }

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
    mapa->drawSuperior(win);

 /// OBJECT ///

    for( unsigned j = 0; j < objetos.size(); j++)
        win->draw(objetos[j]->getSprite());

    win->setView(viewHud);

    timeToString();
    win->draw(*txt_time);


    win->draw(*txt_nrondas);






    /// HUD (AMMO DISPLAY, RONDAS, ETC

    hud->drawHud(win);

    win->draw(player->getScoreTxt());
    win->draw(player->getLifeBox());
    win->draw(player->getLifeTxt());
    win->draw(player->getShieldBox());
    win->draw(player->getShieldTxt());

    hud->setTxtAmmo(player->getArmaActiva().getMunicion());

        /// RONDAS ///
        if(control_rondas > 0)
            win->draw(*txt_ronda);
        ///TXT objetos///
        if(control_obj > 0)
            win->draw(*txt_objetos);

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
       // if(player->getPosition().y > 0)
            y = -1;
    }
    else if( Keyboard::isKeyPressed(Keyboard::S))
    {
       //) if(player->getPosition().y < winDim.y)
            y = 1;
    }
    if( Keyboard::isKeyPressed(Keyboard::A))
    {
      //  if(player->getPosition().x > 0)
            x = -1;
    }

    if( Keyboard::isKeyPressed(Keyboard::W))
    {
       // if(player->getPosition().y > 0)
            y = -1;
    }
    else if( Keyboard::isKeyPressed(Keyboard::S))
    {
       //) if(player->getPosition().y < winDim.y)
            y = 1;
    }
    if( Keyboard::isKeyPressed(Keyboard::A))
    {
      //  if(player->getPosition().x > 0)
            x = -1;
    }

    else if( Keyboard::isKeyPressed(Keyboard::D))
    {
        //if(player->getPosition().x < winDim.x)
            x = 1;
    }
    if(x!=0 || y!=0)
        player->move(x, y, game_timer);


  if( Keyboard::isKeyPressed(Keyboard::Space))
    {
        if(player->getArmaActiva().getNombre()=="Pistola" && bullet_cooldown.asSeconds() >= .5f)
        {
            pistola_sound.play();
            bullet_clock.restart();
            balas.push_back(new Bullet(player->getPosition(), player->getDir(), 5, *tex_balas, "Pistola"));//ultimo parametro radio a falta de implementar diferentes tipos de bala
            //cout<<player->getArmaActiva().getNombre()<<": "<<player->getArmaActiva().getMunicion()<<endl;

        }
        if(player->getArmaActiva().getNombre()=="Carabina" && bullet_cooldown.asSeconds() >= .2f)
        {
            if(player->getArmaActiva().getMunicion()>0)
            {
                carbine_sound.play();
                bullet_clock.restart();
                balas.push_back(new Bullet(player->getPosition(), player->getDir(), 3, *tex_balas, "Carabina"));//ultimo parametro radio a falta de implementar diferentes tipos de bala
                player->quitarBalaActiva();
            }
            else
            {
                    //cout<<player->getArmaActiva().getNombre()<<": SIN MUNICION"<<endl;
                    player->cambiarArma();
                    hud->setGun(player->getArmaActiva().getNombre());//cambiar arma en el hud del ammo
            }

        }
        if(player->getArmaActiva().getNombre()=="Escopeta" && bullet_cooldown.asSeconds() >= .9f)
        {
            if(player->getArmaActiva().getMunicion()>0)
            {
                 shotgun_sound.play();
                 bullet_clock.restart();
                 balas.push_back(new Bullet(player->getPosition(), player->getDir(), 7, *tex_balas, "Escopeta"));//ultimo parametro radio a falta de implementar diferentes tipos de bala
                 player->quitarBalaActiva();
                //cout<<player->getArmaActiva().getNombre()<<": "<<player->getArmaActiva().getMunicion()<<endl;
            }
            else
            {
                   // cout<<player->getArmaActiva().getNombre()<<": SIN MUNICION"<<endl;
                   player->cambiarArma();
                   hud->setGun(player->getArmaActiva().getNombre());//cambiar arma en el hud del ammo
            }
        }
    }

    for(unsigned i=0; i<balas.size(); i++)
        balas[i]->move(game_timer);



}


void Game::colisiones()
{

    for(unsigned i=0; i<balas.size(); i++)
    {
        Vector2f aux = balas[i]->getPos();
       if(aux.x < 0 || aux.x > 1600 || aux.y < 0 || aux.y > 1600)
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



void Game::colisionMapPlayer(int i){

    /*Este metodo hace que la capa i sea colisionable tanto con emeigos como con el player, si al final decidimos que los enemigos no colisionan con nada
    se comenta el bucle for de enemigos y listo.*/
    if(i == 1)
    {
        for(int fil=0; fil<mapa->getAltura(); fil++)
        {
            for(int col=0; col<mapa->getAnchura(); col++)
            {

                if(mapa->getMapaSprites()[i][fil][col]!=NULL)
                {

                        if(mapa->getMapaSprites()[i][fil][col]->getGlobalBounds().intersects(player->getBoundsBox()))
                        {

                            //player->move(player->getDir().x*-1, player->getDir().y*-1,game_timer);
                            //player->setDir({player->getDir().x*-1, player->getDir().y*-1});
                            player->collisionMove(player->getDir().x*-1, player->getDir().y*-1, game_timer);
                        }
                }

            }
        }

    }else{
        for(int fil=0; fil<mapa->getAltura(); fil++)
        {
            for(int col=0; col<mapa->getAnchura(); col++)
            {

                if(mapa->getMapaSprites()[i][fil][col]!=NULL)
                {
                        FloatRect extra = player->getBoundsBox();

                        if(mapa->getMapaSprites()[i][fil][col]->getGlobalBounds().intersects(extra))
                        {
                                cout<<extra.width<<endl;
                        cout<<extra.height<<endl;
                            //player->move(player->getDir().x*-1, player->getDir().y*-1,game_timer);
                            //player->setDir({player->getDir().x*-1, player->getDir().y*-1});
                            player->collisionMove(player->getDir().x*-1, player->getDir().y*-1, game_timer);
                        }
                }

            }
        }

    }


}

void Game::colisionMapEnemy(int i){ //para las capas que colisionan

    for(int fil=0; fil<mapa->getAltura(); fil++)
    {
        for(int col=0; col<mapa->getAnchura(); col++)
        {

            if(mapa->getMapaSprites()[i][fil][col]!=NULL)
            {

                for(int j=0; j<enemigos.size(); j++) //este
                {
                    if(mapa->getMapaSprites()[i][fil][col]->getGlobalBounds().intersects(enemigos[j].getBounds()))
                    {
                        Vector2f enemydir = enemigos[j].getDir(player->getPosition());
                        enemigos[j].move(enemigos[j].getDir(player->getPosition()).x*-1, enemigos[j].getDir(player->getPosition()).y*-1,game_timer);
                    }

                    for(unsigned z=0; z<balas.size();z++)
                        if(mapa->getMapaSprites()[i][fil][col]->getGlobalBounds().intersects(balas[z]->getBounds()))
                        {
                            borrarBala(z);
                            cout<<"c"<<endl;
                        }
                }

            }

        }

    }


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
        if(cont_rondas!=0 && cont_rondas%2!=0){
        Enemy aux(*tex_enemy_perro,s, (int)60, 2);
        enemigos.push_back(aux);
        crearBlood();
        } else{ // Si quitas el else, mezclas en una misma ronda diferentes enemigos
        Enemy aux(*tex_enemy,s, (int)100, 0);
        enemigos.push_back(aux);
        crearBlood();}
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
           enemigos[i].move(v_vectores, game_timer);//se pasa el array con solo una pos, la del player.

        else
        {
            for(unsigned k = 0; k<indices.size();k++)//meto al array de posiciones la pos de los enemigos que estan cerca del enemigo actual
            {   unsigned ind = indices[k];
                v_vectores.push_back(enemigos[ind].getPosition());

            }
            enemigos[i].move(v_vectores, game_timer);

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
            int x=0;
            int y=0;
            if(enemigos[i].getPosition().x > player->getPosition().x)
            {
                x=-1;
            }
            else
            {
                x=1;
            }
            if(enemigos[i].getPosition().y > player->getPosition().y)
            {
                y=-1;
            }
            else
            {
                y=1;
            }
            player->empujon(x, y, game_timer);

            player->gestionaVida(-10);
            break;
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
                updateObjetoTxt(1);
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
                updateObjetoTxt(2);
            }
            else if(aux=="p")
            {
                //cout<<"Planchadito: Recuperamos toda la vida"<<endl;
                player->setLife(100-player->getLife());
                updateObjetoTxt(0);
            }
            else if(aux=="m")
            {
                //cout<<"Modo PaTo: matas a todos de un tiro"<<endl;
                //player->getSprite().setColor(Color::Red);


                modoPatoON();

                updateObjetoTxt(5);
            }
            else if(aux=="ammoC")
            {
                player->cogerMunicion("Carabina", 50);
                updateObjetoTxt(3);

            }

            else if(aux=="ammoE")
            {
                player->cogerMunicion("Escopeta", 10);
                updateObjetoTxt(4);

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
void Game::updateRondaTxt()
{

    std::string out_string;
    std::stringstream ss;
    ss << cont_rondas+1;
    out_string = ss.str();
    txt_ronda->setString("Ronda: "+out_string);
    control_rondas = general_clock.getElapsedTime().asSeconds();
}
void Game::updateObjetoTxt(int objj)
{
    //0 planchadito  -  1 botijola  - 2 duknamite  - 3 amo carabina  - 4 amo escopeta  - 5 PATO

    if(objj == 0)
    {
        txt_objetos->setString("Planchadito: Recuperas la Vida");
        control_obj = general_clock.getElapsedTime().asSeconds();
    }else if(objj == 1)
    {
        txt_objetos->setString("Botijola: Recuperas el Escudo");
        control_obj = general_clock.getElapsedTime().asSeconds();
    }else if(objj == 2)
    {
        txt_objetos->setString("Ducknamite: kabooom");
        control_obj = general_clock.getElapsedTime().asSeconds();
    }else if(objj == 3)
    {
        txt_objetos->setString("Municion: +50 balas de Carabina");
        control_obj = general_clock.getElapsedTime().asSeconds();

    }else if(objj == 4)
    {
        txt_objetos->setString("Municion: +10 balas de Escopeta");
        control_obj = general_clock.getElapsedTime().asSeconds();
    }else if(objj == 5)
    {
        txt_objetos->setString("Modo P.A.T.O: Insta Kill");
        control_obj = general_clock.getElapsedTime().asSeconds();
    }


}

