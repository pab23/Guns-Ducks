#include "Map.h"
#include "tinyxml.h"
#include "tinystr.h"
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

Map::Map()
{
    //ctor
    numCapas=0;

}

Map::~Map()
{
    for(int cont=0; cont<numCapas; cont++){
        for(int cont2; cont2<altura; cont2++){
            delete[] mapaTiles[cont][cont2];
        }
    delete[] mapaTiles[cont];
    }
    delete[] mapaTiles;
}

Map::Map (const Map& aux) {

}

void Map::leerMap(int nn){
TiXmlDocument doc;
//En el caso de tener varios mapas que se pasarian por parametro se carga uno u otro
if(nn==1)
    {
    doc.LoadFile("resources/MapaManoCesped.tmx");
    cout<<"entro mal"<<endl;
}
else if(nn==2)
{
    cout<<"entro bien"<<endl;
    doc.LoadFile("resources/MapaManoTierra.tmx");
}
TiXmlElement* mapaxml=doc.FirstChildElement("map");

//Metadatos del tmx
mapaxml-> QueryIntAttribute("width", &anchura);
mapaxml-> QueryIntAttribute("height", &altura);
mapaxml-> QueryIntAttribute("tilewidth", &tileAnchura);
mapaxml-> QueryIntAttribute("tileheight", &tileAltura);

cout<<"datos: " <<anchura<<" "<<altura<<endl;
//Almacena nuestros tilesets (En mapa 1, terreno, arbol y tiles3)
TiXmlElement *sets = mapaxml->FirstChildElement("tileset");

/*
while(sets){
    sets=sets->NextSiblingElement("tileset");
    cont++;
    //Revisable
}*/
//Ahora se guardan las imagenes en la variable PROBLEMA TENEMOS VARIOS TILESETS
string archivo;
//sets=mapaxml->FirstChildElement("tileset");

/*while(sets){
    sets=sets->NextSiblingElement("tileset");
}*/
archivo=(string)sets->FirstChildElement("image")->Attribute("source");

//Guardamos Capichis
tsetTexture.loadFromFile(archivo);
//numCapas=0;
TiXmlElement *capa = mapaxml->FirstChildElement("layer");
numCapas=0;
while(capa){
    capa=capa->NextSiblingElement("layer");
    numCapas++;
}
// genera la matriz tridimensional donde
//guarda la capa, y la posicion en x e y de cada sprite, nos hace falta para
//guardar el gid que se 	usa en cada momento
//Almacenamos las capas, y luego primer bucle donde almacenamos la altura




mapaTiles=new int**[numCapas];
for(int cont=0; cont<numCapas; cont++){
    mapaTiles[cont]=new int*[altura];
}
//Segundo bucle donde guardamos la anchura
for(int cont2=0; cont2<numCapas; cont2++){
    for(int cont3=0; cont3<altura; cont3++){
        mapaTiles[cont2][cont3]=new int[anchura];
    }
}
//Vamos ahora a pillar los gid
TiXmlElement *datos;
string *nombre=new string[numCapas];;
capa=mapaxml->FirstChildElement("layer");

int var1, var2;
var1=0;
var2=0;
while(capa){
    datos=capa->FirstChildElement("data")->FirstChildElement("tile");
    nombre[var1]=(string)capa->Attribute("name");
    while(datos){
        for(int var3=0; var3<altura; var3++){
            for(int var4=0; var4<anchura; var4++){
                    datos->QueryIntAttribute("gid", &mapaTiles[var1][var3][var4]);
                    datos=datos->NextSiblingElement("tile");
            }
        }
    }
    //var2++;
    var1++;
    capa=capa->NextSiblingElement("layer");
}

//Guardamos los sprites bonitos

mapaSprites=new Sprite***[numCapas];

for (int num1=0; num1<numCapas; num1++){
    mapaSprites[num1]=new sf::Sprite**[altura];
}

for (int num1=0; num1<numCapas; num1++){

    for(int num2=0; num2<altura; num2++){
            mapaSprites[num1][num2]=new sf::Sprite*[anchura];

        for(int num4=0; num4<anchura;num4++){
            mapaSprites[num1][num2][num4]=new sf::Sprite();
        }
    }

}

int filas = tsetTexture.getSize().y/tileAltura;
int columnas = tsetTexture.getSize().x/tileAnchura;
tsetSprites=new sf::Sprite[filas*columnas]; //Espacio para las imagenes

int aux=0;
//tileset nos lo guardamos
for(int fil=0; fil<filas;fil++){
    for(int col=0; col<columnas; col++){
        tsetSprites[aux].setTexture(tsetTexture);
        tsetSprites[aux].setTextureRect(sf::IntRect(col*tileAnchura, fil*tileAltura, tileAnchura, tileAltura));
        aux++;
    }
}
//A dibujar

for(int cap=0; cap<numCapas; cap++){
    for(int fil=0; fil<altura; fil++){
        for(int col=0; col<anchura; col++){
            int gid=mapaTiles[cap][fil][col]-1;
            if(gid>=filas*columnas){
                //cout<<"Error en el calculo de tiles"<<endl;
            }else if(gid>0){
              //  cout<<"rellenndado spires"<<endl;
                mapaSprites[cap][fil][col]=new sf::Sprite(tsetTexture, tsetSprites[gid].getTextureRect());
                mapaSprites[cap][fil][col]->setPosition(col*tileAnchura, fil*tileAltura);
           //cout<<cap<<" "<<fil<<" "<<col<<endl;

            }else{

                mapaSprites[cap][fil][col]=NULL;
            }

        }
    }
}
/*cout<<"Datos del mapa:"<<endl;
    cout<<"Heigth= "<<altura<<endl;
    cout<<"Width= "<<anchura<<endl;
    cout<<"TileWidth= "<<tileAltura<<endl;
    cout<<"TileHeigth= "<<tileAnchura<<endl;
    cout<<"Numero de capas= "<<numCapas<<endl;
   // cout<<"Numero de tilesets= "<<numTil<<endl;
    cout<<"Nombre del tileset= "<<archivo<<endl;
    cout<<endl;
*/
}

void Map::draw(sf::RenderWindow* window){
//cout<<"numeor de cpasa"<<numCapas<<endl;
//cout<<"numeor de cpasa"<<altura<<endl;
//cout<<"numeor de cpasa"<<anchura<<endl;


for(int cap=0; cap<numCapas; cap++){

    for(int fil=0; fil<altura; fil++){

        for(int col=0; col<anchura; col++){
            // cout<<"pintando sprites"<<endl;
            if(mapaSprites[cap][fil][col]!=NULL){
                //window->draw(tsetSprites[0]);
                //cout<<"pintando sprites ahor si"<<mapaSprites[cap][fil][col]<<endl;

                        if(cap!=3 && cap!=1){
                            window->draw(*(mapaSprites[cap][fil][col]));
                        }




            }
        }
    }

}

}
void Map::drawSuperior(sf::RenderWindow* window){

     for(int fil=0; fil<altura; fil++){

        for(int col=0; col<anchura; col++){
            // cout<<"pintando sprites"<<endl;
            if(mapaSprites[3][fil][col]!=NULL){
                //window->draw(tsetSprites[0]);
                //cout<<"pintando sprites ahor si"<<mapaSprites[cap][fil][col]<<endl;


                            window->draw(*(mapaSprites[3][fil][col]));
                        }




            }
        }
    }

void Map::drawBases(sf::RenderWindow* window){

     for(int fil=0; fil<altura; fil++){

        for(int col=0; col<anchura; col++){
            // cout<<"pintando sprites"<<endl;
            if(mapaSprites[1][fil][col]!=NULL){
                //window->draw(tsetSprites[0]);
                //cout<<"pintando sprites ahor si"<<mapaSprites[cap][fil][col]<<endl;


                            window->draw(*(mapaSprites[1][fil][col]));
                        }




            }
        }
    }


bool Map::compruebaColision(sf::FloatRect &fr){

    for(int fil=0; fil<altura; fil++){
        for(int col=0; col<anchura; col++){
            // cout<<"pintando sprites"<<endl;
            if(mapaSprites[2][fil][col]!=NULL){
                if(fr.intersects(mapaSprites[2][fil][col]->getGlobalBounds())){
                    return true;
                }
            }
        }
    }
    return false;

}

int Map::getAltura(){
    return altura;
}
int Map::getAnchura(){
    return anchura;
}
Sprite**** Map::getMapaSprites(){
    return mapaSprites;
}

