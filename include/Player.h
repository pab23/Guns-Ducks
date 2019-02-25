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


    protected:

    private:
        Sprite *spr;
        RectangleShape box;
        float speed;
};

#endif // PLAYER_H
