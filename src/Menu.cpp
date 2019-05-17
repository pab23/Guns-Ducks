#include "Menu.h"

Menu::Menu(Vector2i dim)
{
    selected = 0;
    bg = new Texture();
    bg->loadFromFile("resources/portada.png");
    sp = new Sprite(*bg);
    fuente = new Font();
    fuente->loadFromFile("letra_pixel.ttf");
    tx = new Texture();
    tx->loadFromFile("resources/menu-item.png");
    int it = 0;
    texto[0] = new Text("PLAY GAME", *fuente);
    texto[1] = new Text("HOW TO PLAY", *fuente);
    texto[2] = new Text("QUIT", *fuente);
    for(unsigned i = 0; i < 3; i++)
    {
        items[i] = new Sprite(*tx);
        items[i]->setOrigin(150, 25);
        items[i]->setPosition(dim.x/2, dim.y/2+it);
        texto[i]->setOrigin(150,25);
        texto[i]->setPosition(dim.x/2+30, dim.y/2+it+6);
        texto[i]->setColor(Color::White);
        it += 60;

    }
    texto[0]->setColor(Color::Black);
}

Menu::~Menu()
{
    for(unsigned i = 0; i < 3; i++)
    {
        delete items[i];
        delete texto[i];
    }
    delete fuente;
    delete tx;
    delete sp;
    delete bg;
}


void Menu::moveUp()
{
    if(selected -1 >= 0)
    {
        texto[selected]->setColor(Color::White);
        selected--;
        texto[selected]->setColor(Color::Black);
    }
}

void Menu::moveDown()
{
    if(selected +1 <= 2)
    {
        texto[selected]->setColor(Color::White);
        selected++;
        texto[selected]->setColor(Color::Black);
    }
}

void Menu::draw(RenderWindow &win)
{

    win.draw(*sp);
    for(unsigned i = 0; i < 3; i++)
    {

        win.draw(*items[i]);
        win.draw(*texto[i]);
    }


}

int Menu::getSelected()
{
    return selected;
}
