#include "Hud.h"

Hud::Hud(Texture tex)
{


    modopato = false;

    font = new Font();
    font->loadFromFile("MYRIADPRO-BOLD.OTF");

    tex_ammo = new Texture(tex);
    spr_ammo = new Sprite(*tex_ammo);
    spr_ammo->setScale(.7,.7);
    spr_ammo->setPosition(500,500);


    spr_life = new Sprite(*tex_ammo);

    spr_life->setTextureRect(IntRect(94,313,265,40));

    spr_life->setTextureRect(IntRect(126,313,265,40));

    spr_life->setPosition(507,457);




    txt_bullet = new Text();
    txt_bullet->setFont(*font);
    txt_bullet->setCharacterSize(45);
    FloatRect textRect = txt_bullet->getLocalBounds();
    txt_bullet->setOrigin(textRect.width/2,textRect.height/2);
    txt_bullet->setPosition(650,508);
    txt_bullet->setColor(Color(220,224,223));


    spr_duckdead =new Sprite(*tex_ammo);

    spr_duckdead->setTextureRect(IntRect(0,302,80,100));

    spr_duckdead->setTextureRect(IntRect(30,302,80,100));

    spr_duckdead->setPosition(10, 80);
    spr_duckdead->setScale(.35,.35);
    txt_duckdead = new Text();
    txt_duckdead->setFont(*font);
    txt_duckdead->setCharacterSize(28);
    txt_duckdead->setPosition(spr_duckdead->getPosition().x+35,spr_duckdead->getPosition().y);
    txt_duckdead->setColor(Color::White);



    spr_instakill =new Sprite(*tex_ammo);
    spr_instakill->setTextureRect(IntRect(0,415,156,130));
    spr_instakill->setPosition(400, 15);
    spr_instakill->setScale(.7,.7);

    txt_duckdead->setColor(Color::White);


    setTxtDuckdead(0);


    setGun("Pistola");
}


void Hud::drawHud(RenderWindow* win){
    win->draw(*spr_duckdead);
    win->draw(*txt_duckdead);



    if(modopato)win->draw(*spr_instakill);


    win->draw(*spr_life);
    win->draw(*spr_ammo);
    if(*str_gun == "Carabina" || *str_gun == "Escopeta")win->draw(*txt_bullet);
}

void Hud::setGun(string gun){
    if(gun=="Pistola")
        spr_ammo->setTextureRect(IntRect(30,0,400,100));
    else if(gun=="Carabina")
        spr_ammo->setTextureRect(IntRect(30,100,400,100));
    else if(gun=="Escopeta")
        spr_ammo->setTextureRect(IntRect(30,200,400,100));


    str_gun = new string(gun);
}

void Hud::setTxtAmmo(int n){

    if(*str_gun == "Carabina" || *str_gun == "Escopeta"){
        std::stringstream ss;
        ss << n;
        txt_bullet->setString(ss.str());
    }

}

void Hud::setTxtDuckdead(int n){


        std::stringstream ss;
        ss << n;
        txt_duckdead->setString(ss.str());


}



void Hud::setModoPato(bool b){modopato = b;}


