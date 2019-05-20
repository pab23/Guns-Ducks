#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

using namespace std;
using namespace sf;

class Menu
{
    public:
        Menu(Vector2i);
        virtual ~Menu();

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

        void draw(RenderWindow &);

        int getSelected();
        int getMapSelected();
        int getState();
        void setState(int);
        void muteMusic();

    protected:

    private:
        int selected, state, map_selected;
        Sprite *items[3], *maps[2], *key;
        Text *texto[3], *map_text[2];
        Font *fuente;
        Texture *tx, *bg, *map_tex, *binding;
        Sprite* sp;
        Sound *music;
        SoundBuffer *music_buffer;
};

#endif // MENU_H
