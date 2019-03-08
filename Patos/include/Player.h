#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
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
        int getScore();
        Text getScoreTxt();
        void setScore(int);
        RectangleShape getLifeBox();
        int getLife();
        void setLife(int);
        Text getLifeTxt();




    protected:

    private:
        Sprite *spr;
        RectangleShape *box;
        float speed;
        Vector2i dir;
        int score = 0;
        Text * txt_score;
        Font * font_txt;
        //Life
        int life;
        RectangleShape *life_box;
        Text *txt_life;

};

#endif // PLAYER_H
