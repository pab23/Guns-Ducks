#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Menu
{
    public:
        Menu(Vector2i);
        virtual ~Menu();

        void moveUp();
        void moveDown();

        void draw(RenderWindow &);

        int getSelected();

    protected:

    private:
        int selected;
        Sprite *items[3];
        Text *texto[3];
        Font *fuente;
        Texture *tx, *bg;
        Sprite* sp;
};

#endif // MENU_H
