#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "AnimatedSprite.h"
#include "Animation.h"
#include "Blood.h"


/** VALORES POR DEFECTO PARA EL CONTROL DE DE ENEMIGOS Y OLEADAS **/
#define kEnemy_reward 10
#define T_OLEADAS 5 //tiempo en segundos que transcurre antes de crear una nueva oleada de enemigos
#define N_OLEADAS 4 //nº de oleadas que se van a crear
#define N_ENEMIES_OLEADA 5 //nº de enemigos por oleada


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
        void crearEnemy(int n);
        void crearAnimaciones();
        void colisiones();
        void colisionBox();
        void timeToString();
        void inZona();
        int getEnemyRespawn();
        void crearBlood();
        void posicionarBlood(Vector2f pos);




    protected:

    private:

        RenderWindow *win;
        Texture *tex_player,*tex_bloods, *tex_enemy;
        Player *player;
        Event e;
        int enemyRespawn; //nº de oleadas
        vector<Enemy> enemigos;
        vector<Blood> bloods;
        vector<Bullet> balas;
        Clock bullet_clock, general_clock, zone_clock,  enemy_clock,frame_clock;
        Time bullet_cooldown, enemy_timer, general_timer, zone_timer;
        Vector2i winDim;
        bool primer, info;
        Text *txt_time;
        Font *font;
        RectangleShape *life_zone;





};

#endif // GAME_H
