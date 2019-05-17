#ifndef GUN_H
#define GUN_H
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Gun
{
    public:
        Gun(string, int);
        void setMunicion(int);
        int getMunicion();
        string getNombre();


    protected:

    private:
        string nombre;
        int municion;
};

#endif // GUN_H
