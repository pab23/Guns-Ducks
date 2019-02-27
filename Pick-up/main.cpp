#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/Game.h"



using namespace sf;
using namespace std;

const Vector2i winDim (800, 600);


int main()
{
    Game juego(winDim);
    return EXIT_SUCCESS;
}
