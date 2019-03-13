#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Player
{
    public:
        Player(){}
        Player(Texture&);

        void move(int, int);

        Sprite getSprite();
        Vector2f getPosition();
        Vector2i getDir();
        CircleShape getCircle();
        FloatRect getBounds();
        FloatRect getBoundsBox();
        void setPosition(Vector2f vec);
        RectangleShape getRect();
        //void cambiarAnimacion();
        int getScore();
        Text getScoreTxt();
        void setScore(int);
        RectangleShape getLifeBox();
        RectangleShape getShieldBox();
        int getLife();
        int getShield();
        void setLife(int);
        void setShield(int);
        Text getLifeTxt();
        Text getShieldTxt();
        void gestionaVida(int);


    protected:

    private:
        Sprite *spr;
        RectangleShape *box, *life_box, *shield_box;
        CircleShape *circle;//para que enemigos rodeen al player
        float speed;
        Vector2i dir;
        int score = 0;
        Text * txt_score;
        Font * font_txt;
        //Life
        int life, shield;
        Text *txt_life, *txt_shield;

};

#endif // PLAYER_H