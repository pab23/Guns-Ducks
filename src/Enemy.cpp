#include "../include/Enemy.h"
#include <math.h>

Enemy::Enemy(Texture &tex, float vel, int vida, int tipo)
{

    Vector2i origen(400,420); Vector2i sizeVentana(800,800);
    Vector2f pos = this->getRandomPosition(origen, sizeVentana);
    speed = vel*tipo;
    if(speed==0){
        speed=vel;
    }
    spr = new Sprite(tex);
    spr->setOrigin(24/2,24/2);
    spr->setTextureRect(IntRect(0*75, 0*75, 24, 24));
    spr->setPosition(pos);
    spr->scale(1.5,1.5);
    hp = vida;
    anim = new Animation(tex,tipo);

    box = new RectangleShape({spr->getTextureRect().width,spr->getTextureRect().height/4});
    box->setFillColor(Color::Red);
    box->setOrigin(box->getSize().x/2,box->getSize().y/2);
    box->setPosition(getPosition().x,getPosition().y+spr->getTextureRect().height/3);


    //direction = {0,0};
}

Enemy::~Enemy()
{
    /*delete spr;
    delete box;
    delete anim;
    speed = hp = dist_col = 0;
    dir = {0, 0};*/

}

Sprite Enemy::getSprite()
{
    return *spr;
}

FloatRect Enemy::getBounds(){
    return spr->getGlobalBounds();
}
FloatRect Enemy::getBoundsBox(){
    return box->getGlobalBounds();
}
Vector2f Enemy::getPosition(){
    return spr->getPosition();
}
void Enemy::setColor(int color)
{
    if(color == 0)
    box->setFillColor(Color::Green);
    else
    box->setFillColor(Color::Red);
}

RectangleShape Enemy::getRect()
{
    return *box;
}
void Enemy::setPosition(float x, float y){
    spr->setPosition(x,y);
    box->setPosition(x,y+spr->getTextureRect().height/3);
}
void Enemy::setPosition(Vector2f vec){
    spr->setPosition(vec.x,vec.y);
    box->setPosition(vec.x,vec.y+spr->getTextureRect().height/3);
}
void Enemy::move(vector<Vector2f> v_posiciones, float time){


    vector<Vector2f> vectores;
    Vector2f playerPosition,position, direction, normalizedDir, currentSpeed;
    float aux = .8;//peso del vector de repulsion del enemigo

    for(unsigned i = 0;i < v_posiciones.size();i++)
    {

        position = v_posiciones[i];//En el primer indice del vector siempre estara la pos del player
        if(i == 0)//No tiene enemigos cerca
            direction = position - getPosition();//Vector que une player-enemigo
        else{
            Vector2f vaux = position - getPosition();//Si tiene un enemigio cerca, calculo el vector entre ambos enemigos,lo multiplico por un factor y lo resto al vector enemigo-player
            direction -= (vaux*aux);
        }

    }

        normalizedDir.x = direction.x / (sqrt(pow(direction.x, 2) + pow(direction.y, 2)));//Normalizamos el vector para convetirlo en unitario
        normalizedDir.y = direction.y / (sqrt(pow(direction.x, 2) + pow(direction.y, 2)));
        currentSpeed = normalizedDir * speed * time;//v.unitario * escalar, ahora tenemos modulo(velocidad) y direccion (vector direction)*Creo que esa es la teoria


        if(direction.x < 0) dir.x = -1;
        else dir.x = 1;

        if(direction.y < 0)dir.y = -1;
        else dir.y = 1;

        Vector2f posP,posE;
        posP = v_posiciones[0];
        posE = getPosition();

        if(posE.x <= posP.x+30 && posE.x >= posP.x -30)dir.x = 0;
        if(posE.y <= posP.y+30 && posE.y >= posP.y -30)dir.y = 0;

        spr->move(currentSpeed);
        box->move(currentSpeed);




}
float Enemy::getDistance(Vector2f posEnemy){
    Vector2f direction =  posEnemy - getPosition();//Vector que une enemigo-enemigo
    float dist = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    //cout << dist << endl;


    return dist;
}
VertexArray Enemy::getLinePlayerEnemy(Vector2f playerPosition){

        VertexArray l_playerEnemy(Lines, 2);
        l_playerEnemy[0].position = getPosition();
        l_playerEnemy[1].position = playerPosition;


    return l_playerEnemy;
}
VertexArray Enemy::getLineEnemyEnemy(Vector2f posEnemy){

        Color c;
        VertexArray l_EnemyEnemy(Lines, 2);
        l_EnemyEnemy[0].position = getPosition();
        l_EnemyEnemy[1].position = posEnemy;

        if(getDistance(posEnemy) <dist_col)c = Color::Red;
        else c = Color::Green;

        l_EnemyEnemy[0].color = c;
        l_EnemyEnemy[1].color = c;


    return l_EnemyEnemy;
}
vector<unsigned> Enemy::getEnemyArround(vector<Enemy>& enemigos){

    vector<unsigned> indices;
    bool bol = false;
      for(int i=0;i<enemigos.size();i++)
        {

            if(getPosition() != enemigos[i].getPosition())//Evita comparar un enemigo consigo mismo dentro del array enemigos
            {
                float dist = getDistance(enemigos[i].getPosition());
                if(dist < dist_col)indices.push_back(i);
            }

        }
        return indices;
}
int Enemy::RandomNumber( int inicio, int fin ){


     /*
      Genera un número aleatorio entre
      inicio y fin.
     */

     int resultado = 0;

     // Calculamos el margen entre inicio y fin
     int margen = fin - inicio;

     // Establecemos el comienzo del intervalo
     int comienzo = inicio;

     // Comprobamos si el intervalo está al revés
     if( inicio > fin ){

      // Cambiamos el comienzo
      comienzo = fin;

      // Cambiamos el signo de la diferencia
      margen = margen * -1;
     }

     /*
      * Añadimos uno al margen ya que la función
      * rand calcula entre el 0 y uno menos que
      * el margen.
      */
     margen++;

     /*
      Si el intervalo no comienza y acaba en el
      mismo número.
     */

     // Generamos el número aleatorio.
     resultado = comienzo + (rand() % margen);

     return resultado;
}
Vector2f Enemy::getRandomPosition(Vector2i origin, Vector2i sizeV){

    int ox,oy,width,height;
    ox = origin.x; oy = origin.y;
    width = sizeV.x;  height = sizeV.y;

    //Establecemos de que pared sale. 1=left, 2=down, 3=right,4=up
    int a = RandomNumber(1,4);
    int posx,posy;
    switch(a)
    {
        case 1: posx = ox -50;
                posy = oy + RandomNumber(0,height);
        break;

        case 2: posy=oy+height+50;
                posx = ox + RandomNumber(0,width);
        break;

        case 3: posx= ox + width + 50;
                posy=oy + RandomNumber(0,height);
        break;

        case 4: posy= oy -50;
                posx = ox + RandomNumber(0,width);
        break;

    }
    return Vector2f(posx,posy);
}

void Enemy::setVida(string gun)
{
    int dmg = 0;

    if(gun=="Carabina")
    {
        dmg=-40;
    }
    else if(gun=="Pistola")
    {
        dmg=-50;
    }
    else if(gun=="Escopeta")
    {
        dmg=-120;
    }
    hp += dmg;
}

int Enemy::getVida()
{
    return hp;
}

void Enemy::setHp(int n)
{
    hp=n;
}
void Enemy::changePos(Vector2i dire, int obj, Vector2f posi)
{
    anim->changePos(dire, obj, posi);
}
Animation Enemy::getAnim()
{
    return *anim;
}
Vector2i Enemy::getDir()
{
    return dir;
}
void Enemy::setSpr(const Sprite &sprit)
{
    spr = new Sprite(sprit);
}
Vector2f Enemy::getDir(Vector2f playerPosition){

    Vector2f res = playerPosition-this->getPosition();
    if(res.x!=0) //Para pasar la dir como 1s o 0s.
    {
        if(res.x>0){
            res.x=1;
        }
        else{
            res.x=-1;
        }
    }

    if(res.y!=0)
    {
        if(res.y>0){
            res.y=1;
        }
        else{
            res.y=-1;
        }
    }

    return res;


}
void Enemy::move(int x, int y,float time)
{
    float speedX;
    float speedY;

    switch(x)
    {
        case 1:
            speedX = speed;
        break;
        case -1:
            speedX = -speed;
        break;
        default:
            speedX = 0;
        break;
    }
    switch(y)
    {
        case 1:
            speedY = speed;
        break;
        case -1:
            speedY = -speed;
        break;
        default:
            speedY = 0;
        break;
    }


    spr->move(speedX * time, speedY * time);
    //circle->move(speedX, speedY);
    box->move(speedX * time, speedY * time);


}



