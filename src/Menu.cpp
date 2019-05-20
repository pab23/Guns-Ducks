#include "Menu.h"

Menu::Menu(Vector2i dim)
{
    selected = state = 0;
    bg = new Texture();
    bg->loadFromFile("resources/portada.png");
    sp = new Sprite(*bg);
    fuente = new Font();
    fuente->loadFromFile("resources/letra_pixel.ttf");
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
    map_tex = new Texture();
    map_tex->loadFromFile("resources/maps.png");
    maps[0] = new Sprite(*map_tex);
    maps[0]->setTextureRect(IntRect(0, 0, 150, 149));
    maps[0]->setOrigin(75, 75);
    maps[0]->setPosition(300, 298);
    maps[1] = new Sprite(*map_tex);
    maps[1]->setTextureRect(IntRect(150, 0, 150, 150));
    maps[1]->setOrigin(75, 75);
    maps[1]->setPosition(500, 300);
    map_text[0] = new Text("FOREST", *fuente);
    map_text[1] = new Text("DESERT", *fuente);
    map_text[0]->setColor(Color::Black);
    map_text[1]->setColor(Color::White);
    map_text[0]->setPosition(248,340);
    map_text[1]->setPosition(448,340);
    map_selected = 0;
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

void Menu::moveLeft()
{
    if(map_selected -1 >= 0)
    {
        map_text[map_selected]->setColor(Color::White);
        map_selected--;
        map_text[map_selected]->setColor(Color::Black);
    }
}
void Menu::moveRight()
{
    if(map_selected +1 <= 1)
    {
        map_text[map_selected]->setColor(Color::White);
        map_selected++;
        map_text[map_selected]->setColor(Color::Black);
    }
}


void Menu::draw(RenderWindow &win)
{

    win.draw(*sp);
    for(unsigned i = 0; i < 3; i++)
    {
        switch(state)
        {
        default:
            win.draw(*items[i]);
            win.draw(*texto[i]);
            break;
        case 1:
            for(unsigned i = 0; i < 2; i++)
            {
                win.draw(*maps[i]);
                win.draw(*map_text[i]);
            }
            break;
        case 2:
            break;
        }

    }


}

int Menu::getSelected()
{
    return selected;
}

int Menu::getMapSelected()
{
    return map_selected;
}

int Menu::getState()
{
    return state;
}

void Menu::setState(int i)
{
    state = i;
}
