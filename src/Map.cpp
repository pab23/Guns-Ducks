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

void Map::leerMap(int map){

TiXmlDocument doc;
//En el caso de tener varios mapas que se pasarian por parametro se carga uno u otro
if(map==1){
   doc.LoadFile ("resources/MapaEstanqueNoCol.tmx");
}
TiXmlElement* mapaxml=doc.FirstChildElement("map");

//Metadatos del tmx
mapaxml-> QueryIntAttribute("width", &anchura);
mapaxml-> QueryIntAttribute("height", &altura);
mapaxml-> QueryIntAttribute("tilewidth", &tileAnchura);
mapaxml-> QueryIntAttribute("tileheight", &tileAltura);

//Almacena nuestros tilesets (En mapa 1, terreno, arbol y tiles3)
TiXmlElement *sets = mapaxml->FirstChildElement("tileset");
int cont;
cont=0;
while(sets){
    sets=sets->NextSiblingElement("tileset");
    cont++;
    //Revisable
}
//Ahora se guardan las imagenes en la variable PROBLEMA TENEMOS VARIOS TILESETS
string archivo;
sets=mapaxml->FirstChildElement("tileset");
while(sets){
    archivo=(string)sets->FirstChildElement("image")->Attribute("source");
    sets=sets->NextSiblingElement("tileset");
}
//Guardamos Capichis
tsetTexture.loadFromFile(archivo);
numCapas=0;
TiXmlElement *capa = mapaxml->FirstChildElement("layer");
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
    for(int cont3=0; cont3<altura; cont3){
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
                    datos->QueryIntAttribute("gid", &mapaTiles[var2][var3][var4]);
                    datos=datos->NextSiblingElement("tile");
        }
    }
}
var2++;
var1++;
capa=capa->NextSiblingElement("layer");
}

//Guardamos los sprites bonitos

mapaSprites=new sf::Sprite***[numCapas];
for (int num1=0; num1<numCapas; num1++){
    mapaSprites[num1]=new sf::Sprite**[altura];
}
for (int num2=0; num2<numCapas; num2++){
    for(int num3=0; num3<altura; num3++){
        mapaSprites[num2][num3]=new sf::Sprite*[anchura];
        for(int num4=0; num4<anchura;num4++){
            mapaSprites[num2][num3][num4]=new sf::Sprite();
        }
    }
}

int filas = tsetTexture.getSize().y/tileAltura;
int columnas = tsetTexture.getSize().x/tileAnchura;
tsetSprites=new sf::Sprite[filas*columnas]; //Espacio para las imagenes

int aux=0;
for(int fil=0; fil<filas;fil++){
    for(int col=0; col<columnas; col++){
        tsetSprites[aux].setTexture(tsetTexture);
        tsetSprites[aux].setTextureRect(sf::IntRect(col*tileAnchura, fil*tileAltura, tileAnchura, tileAltura));
        aux++;
    }
}
//A dibujar
for(int cap; cap<numCapas; cap++){
    for(int fil; fil<altura; fil++){
        for(int col; col<anchura; col++){
            int gid=mapaTiles[cap][fil][col]-1;
            if(gid>0){
                mapaSprites[cap][fil][col]=new sf::Sprite(tsetTexture, tsetSprites[gid].getTextureRect());
                mapaSprites[cap][fil][col]->setPosition(col*tileAnchura, fil*tileAltura);

            }else if(gid>=filas*columnas){
                cout<<"Error en el calculo de tiles"<<endl;
            }else{
                mapaSprites[cap][fil][col]=NULL;
            }

        }
    }
}

}

void Map::draw(sf::RenderWindow* window){
for(int cap; cap<numCapas; cap++){
    for(int fil; fil<altura; fil++){
        for(int col; col<anchura; col++){
            if(mapaSprites[cap][fil][col]!=NULL){
                window->draw(*(mapaSprites[cap][fil][col]));
            }
        }
    }

}
}


