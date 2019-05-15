#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <time.h>
#include <stdlib.h>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Animation.h"
#include "Blood.h"
#include "Gun.h"
#include "Object.h"
#include "Hud.h"
#include "Map.h"



/** VALORES POR DEFECTO PARA EL CONTROL DE DE ENEMIGOS Y OLEADAS **/
#define ENEMY_REWARD 10
#define T_OLEADAS 5 //tiempo en segundos que transcurre antes de crear una nueva oleada de enemigos
#define N_OLEADAS 1 //nº de oleadas que se van a crear
#define N_ENEMIES_OLEADA 20 //nº de enemigos por oleada
#define SPEED_ENEMY 800 //velocidad del enemigo
#define N_RONDAS 1
#define UPDATE_TIME 1000/30


using namespace sf;
using namespace std;

class Game
{
    public:
        Game(Vector2i);

        void gameLoop();
        void loadTextures();
        void listenKeyboard();
        void draw();
        void moverEnemigos();
        void crearEnemy(int , float);
        void crearAnimaciones();
        void colisiones();
        void timeToString();
        void inZona();
        void crearBlood();
        void posicionarBlood(Vector2f);
        void modoPatoON();
        void modoPatoOFF();
        void borrarBala(int);
        void playerCollisions();
        void colisionMapPlayer(int);
        void colisionMapEnemy(int);
        void itemCollisions();
        void update();
        void objRandom(Vector2f);




    protected:

    private:

        RenderWindow *win;
        Texture *tex_player,*tex_bloods, *tex_enemy, *tex_map, *tex_object, *tex_ammo, *tex_icon, *tex_balas;
        Sprite *spr_map, *spr_ammo;
        Player *player;
        Event e;
        int cont_oleadas, cont_rondas, cont_bajas; //contador de oleadas y rondas creadas
        vector<Enemy> enemigos;
        vector<Blood> bloods;
        vector<Bullet*> balas;
        vector<Object*> objetos;
        Clock bullet_clock, general_clock, zone_clock,  enemy_clock,frame_clock,  modoPato_clock, animation_clock, game_clock;
        Time bullet_cooldown, enemy_timer, general_timer, zone_timer, modoPato_timer,animation_timer, game_timer_t;
        Vector2i winDim;
        bool primer, info, modoPato;
        Text *txt_time;
        Font *font;
        RectangleShape *life_zone;
        Hud *hud;
        float game_timer;
        View view, viewHud;
        Map *mapa;
        bool chocando;

};

#endif // GAME_H
