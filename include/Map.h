#ifndef MAP_H
#define MAP_H
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Map
{
    public:
        Map();
        ~Map();
        Map (const Map& aux);

        void leerMap(int map);
        void draw(sf::RenderWindow *window);
        void drawSuperior(sf::RenderWindow *window);
	void drawBases(sf::RenderWindow *window);
        int getAltura();
        int getAnchura();
        Sprite ****getMapaSprites();

    bool compruebaColision(sf::FloatRect &);



    protected:

    private:

        int anchura;
        int altura;
        int tileAnchura;
        int tileAltura;
        int numCapas;
        int *** mapaTiles;

        Sprite * tsetSprites;
        Sprite **** mapaSprites;
        Texture tsetTexture;
        //CREAR UN ARRAY DE TEXTURAS CON · DIFERENTES QUE SEAN LAS · IMAGEENES DISTINTAS PUEDE REVENTAR??????
};

#endif // MAP_H

