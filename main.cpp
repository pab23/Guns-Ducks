#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/Game.h"
#include "include/Menu.h"



using namespace sf;
using namespace std;

const Vector2i winDim (800, 600);



void empezarJuego(RenderWindow &ventana)
{
    Game juego(ventana, 1);
}


int main()
{
    RenderWindow *ventana = new RenderWindow(VideoMode(winDim.x, winDim.y), "Guns & Ducks");
    ventana->setFramerateLimit(60);
    Event e;
    Menu* menu = new Menu(winDim);

    srand(time(NULL));//Semilla para random.No tocar

    while(ventana->isOpen())
    {
        ventana->clear();
        while(ventana->pollEvent(e))
        {
            switch(e.type)
            {
            case Event::KeyReleased:
                switch(e.key.code)
                {
                    case Keyboard::Up:
                        menu->moveUp();
                        break;
                    case Keyboard::Down:
                        menu->moveDown();
                        break;
                    case Keyboard::Return:
                        switch(menu->getSelected())
                        {
                        case 0:
                            delete menu;
                            empezarJuego(*ventana);
                            break;
                        case 1:
                            break;
                        case 2:
                            ventana->close();
                            break;

                        }
                        break;
                }
            default: break;
            }

        }
        menu->draw(*ventana);
        ventana->display();
    }

    return EXIT_SUCCESS;
}
