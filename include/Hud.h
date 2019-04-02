#ifndef HUD_H
#define HUD_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <sstream>


using namespace std;
using namespace sf;


class Hud
{
    public:
        Hud(Texture tex);
        void drawHud(RenderWindow*);
        void setGun(string);
        void setTxtAmmo(int n);

    protected:
    private:
        Texture *tex_ammo;
        Sprite *spr_ammo;
        string *str_gun;
        Font *font;
        Text *txt_bullet;

};

#endif // HUD_H
