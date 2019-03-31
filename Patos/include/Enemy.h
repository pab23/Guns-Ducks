#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <math.h>
#include "../include/Animation.h"

using namespace std;
using namespace sf;

class Enemy
{
    public:

        Enemy(Texture &, float vel);
        ~Enemy();
        Sprite getSprite();
        FloatRect getBounds();
        Vector2f getPosition();
        Vector2i getDir();
        void setPosition(float x, float y);
        void setPosition(Vector2f vec);
        void move(Vector2f playerPosition, bool collision);
        Vector2f getRandomPosition(Vector2i ventana);
        int RandomNumber( int inicio, int fin );
        void setColor(int color);
        FloatRect getBoundsBox();
        RectangleShape getRect();
        Sprite getAnim();





    protected:

    private:
        Sprite *spr;//borrar
        Animation *anim;
        float speed;
        RectangleShape *box;
        Vector2f direction;//Vector de posicion entre el player y el enemigo.Indica la direccion que toma el enemigo para seguir al player.
        Vector2f normalizedDir;//Vector "direction" normalizado.
        Vector2i dir; //Representa el vector direction (hacia donde mira el enemigo) pero en forma de 1,-1 o 0
        Vector2f auxDir;//Vector auxiliar que utilizamos para desviar ligeramente la dirección del enemigo cuando este colisiona con otros enemigos.


};

#endif // ENEMY_H
