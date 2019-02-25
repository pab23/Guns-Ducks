#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
    public:
        Player(){}
        Player(Texture&);

        void move(int, int);

        Sprite getSprite();
        Vector2f getPosition();
        Vector2i getDir();
        RectangleShape getBox();
        void setLife(int);
        int getLife();


    protected:

    private:
        Sprite *spr;
        RectangleShape *box;
        float speed;
        Vector2i dir;
        int life = 100;
};

#endif // PLAYER_H
