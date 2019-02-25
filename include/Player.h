#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
    public:
        Player(){}
        Player(Texture&);

        Sprite getSprite();
        Vector2f getPosition();
        void move(int, int);


    protected:

    private:
        Sprite *spr;
        RectangleShape *box;
        float speed;
        Vector2i dir;
};

#endif // PLAYER_H
