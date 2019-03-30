#ifndef BLOOD_H
#define BLOOD_H

#include "SFML/Graphics.hpp"
#include <iostream>

#define AUX 120;//variable que es el ancho y alto de cada sprite. De momento es 120px

using namespace std;
using namespace sf;

class Blood
{
    public:
    Blood(Texture &);
    void setPosition(Vector2f vec);
    void activar();
    bool getEstado();
    Sprite getSprite();
    Sprite getSprite_pato();
    ~Blood();
    int RandomNumber( int inicio, int fin );//Devuelve un nº aleatorio inicio >= y <= fin


    private:
        Sprite *spr, *spr_pato;
        bool estado;
        int aux;//variable que indica ancho y alto del sprite de sangre a recortar en la textura original.
};

#endif // BLOOD_H
