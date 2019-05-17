#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/Game.h"
#include "include/Menu.h"



using namespace sf;
using namespace std;

const Vector2i winDim (800, 600);



void empezarJuego(RenderWindow &ventana, int select)
{
    Game juego(ventana, select);
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

                    if(menu->getState() == 0)
                    {
                        switch(e.key.code)
                        {
                            case Keyboard::Up:
                                menu->moveUp();
                            break;
                            case Keyboard::Down:
                                menu->moveDown();
                            break;
                        }
                    }
                    else if(menu->getState() == 1)
                    {
                        switch(e.key.code)
                        {
                            case Keyboard::Right:
                                menu->moveRight();
                            break;
                            case Keyboard::Left:
                                menu->moveLeft();
                            break;
                        }
                    }

                    if(e.key.code ==Keyboard::Return)
                    {
                        if(menu->getState() == 0)
                        {
                            switch(menu->getSelected())
                            {
                            case 0:
                                menu->setState(1);
                                break;
                            case 1:
                                break;
                            case 2:
                                ventana->close();
                                break;

                            }
                        }
                        else if(menu->getState() == 1)
                        {
                            empezarJuego(*ventana, menu->getMapSelected()+1);
                        }
                    }


            default: break;
            }

        }
        menu->draw(*ventana);
        ventana->display();
    }

    return EXIT_SUCCESS;
}
