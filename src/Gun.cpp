#include "Gun.h"

Gun::Gun(string name, int ammo)
{
    nombre=name;
    municion=ammo;
}

void Gun::setMunicion(int x)
{
    municion=municion+x;
}

int Gun::getMunicion()
{
    return municion;
}

string Gun::getNombre()
{
    return nombre;
}
