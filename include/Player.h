#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Gun.h"
#include "Animation.h"
#include "Map.h"

using namespace sf;
using namespace std;

class Player
{
    public:
        Player(){}
        Player(Texture&);

        void move(int, int, float);
        void collisionMove(int, int, float);

        Sprite getSprite();
        Vector2f getPosition();
        Vector2f getPositionBox();
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
        void setDir(Vector2i dir);
        Text getLifeTxt();
        Text getShieldTxt();
        void gestionaVida(int);
        Gun getArmaActiva();
        Gun getArmaById();
        void cambiarArma();
        void cogerMunicion(string,int);
        string infoArmaActiva(int);
        void quitarBalaActiva();
        void setSpr(const Sprite&);
        Animation getAnim();
        void changePos(Vector2i, int, Vector2f);
        void empujon(int, int, float);
        Sprite* getSpritePointer(){return spr;};
        void setMapa(Map* mp){mapa=mp;};
        void playDead();
        bool muriendo();

    protected:

    private:
        Sprite *spr;
        Map* mapa;
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
        vector<Gun> armas;
        int armaActiva;
        Animation *anim;
        SoundBuffer dead_buffer;
        Sound dead_sound;

};

#endif // PLAYER_H
