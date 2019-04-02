#include "Hud.h"

Hud::Hud(Texture tex)
{
    tex_ammo = new Texture(tex);
    spr_ammo = new Sprite(*tex_ammo);
    spr_ammo->setScale(.7,.7);
    spr_ammo->setPosition(500,500);

    font = new Font();
    font->loadFromFile("MYRIADPRO-BOLD.OTF");
    txt_bullet = new Text();
    txt_bullet->setFont(*font);
    txt_bullet->setCharacterSize(45);
    txt_bullet->setPosition(650,508);
    txt_bullet->setColor(Color(220,224,223));


    setGun("Pistola");
    setTxtAmmo(60);
}


void Hud::drawHud(RenderWindow* win){
    win->draw(*spr_ammo);
    if(*str_gun == "Carabina" || *str_gun == "Escopeta")win->draw(*txt_bullet);
}

void Hud::setGun(string gun){

    if(gun=="Pistola")
        spr_ammo->setTextureRect(IntRect(0,0,400,100));
    else if(gun=="Carabina")
        spr_ammo->setTextureRect(IntRect(0,100,400,100));
    else if(gun=="Escopeta")
        spr_ammo->setTextureRect(IntRect(0,200,400,100));

    str_gun = new string(gun);
}

void Hud::setTxtAmmo(int n){

    if(*str_gun == "Carabina" || *str_gun == "Escopeta"){
        std::stringstream ss;
        ss << n;
        txt_bullet->setString(ss.str());
    }

}


