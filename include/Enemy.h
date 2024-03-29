#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <math.h>
#include "VertexArray.hpp"
#include "Animation.h"

using namespace std;
using namespace sf;

class Enemy
{
    public:

         Enemy(Texture &, float, int, int);
        virtual ~Enemy();

        Sprite getSprite();
        FloatRect getBounds();//Devuelve la global bounds del sprite enemigo
        Vector2f getPosition();
        RectangleShape getRect();//Devuelve la box del enemigo creada por nosotros
        FloatRect getBoundsBox();//Devuelve la global bounds de la box del enemigo
        VertexArray getLinePlayerEnemy(Vector2f playerPosition);//devuelve las lineas dibujadas entre enemigo y player
        VertexArray getLineEnemyEnemy(Vector2f posEnemy);//devuelve las lineas dibujadas entre enemigo y enemigo
       Vector2f getRandomPosition(Vector2i origin, Vector2i sizeV);//Devuelve una posicion aleatoria (fuera de los margenes) para situar al enemigo
        float getDistance(Vector2f posEnemy);
        Vector2f getDir(Vector2f playerPosition);
        void move(int x, int y,float time);
        void setPosition(float x, float y);
        void setPosition(Vector2f vec);
        void setColor(int color);//Establecer color de la box del enemigo
        void move(vector<Vector2f> v_posiciones, float);
        int RandomNumber( int inicio, int fin );//Devuelve un nº aleatorio inicio >= y <= fin
        vector<unsigned> getEnemyArround(vector<Enemy>& enemigos);
        void setVida(string);
        int getVida();
        void setHp(int);
        void setSpr(const Sprite&);
        void changePos(Vector2i, int, Vector2f);
        Vector2i getDir();
        Animation getAnim();





    protected:

    private:
        Sprite *spr;
        float speed;
        int hp;
        RectangleShape *box;
        //Vector2f direction;//Vector de posicion  player-enemigo.Indica la direccion que toma el enemigo para seguir al player.
        //Vector2f normalizedDir;//Vector "direction" normalizado.
        int dist_col = 50;//Distancia rquerida para la colision entre enemigos
        Animation *anim;
        Vector2i dir;





};

#endif // ENEMY_H
