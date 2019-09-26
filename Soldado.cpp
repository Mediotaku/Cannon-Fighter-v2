#include <iostream>
#include <stdio.h>
#include <cmath>
#include "Soldado.h"
#include <SFML/Graphics.hpp>
#include "Juego.h"
using namespace std;


Soldado::Soldado(){
    if (!texsol.loadFromFile("Texturas/cannon_boy.png")){
        std::cerr << "Error cargando la imagen";
        exit(0);
    }
    if (!texcannon.loadFromFile("Texturas/Cannon_sprite_1.png")){
        std::cerr << "Error cargando la imagen";
        exit(0);
    }
    spritesol.setTexture(texsol);
    spritecannon.setTexture(texcannon);
    spritesol.setOrigin(250,250);
    spritecannon.setOrigin(250,350);
    soldadoX=110; //Rango de movimiento: (110,440)-(95,145)
    soldadoY=440;
    newState.setX(soldadoX);
    newState.setY(soldadoY);
    spritesol.setPosition(soldadoX,soldadoY);
    spritecannon.setPosition(soldadoX,soldadoY);
    spritesol.scale(0.11,0.11);
    spritecannon.scale(0.1,0.1);


}

Soldado* Soldado::instancia=nullptr;

Soldado* Soldado::Instance()
{
    if(!instancia){
    instancia=new Soldado;
    }
    return instancia;
}
float Soldado::getX(){
    return soldadoX;
}
float Soldado::getY(){
    return soldadoY;
}
void Soldado::setX(float nuevo){
    soldadoX=nuevo;
    spritesol.setPosition(soldadoX,spritesol.getPosition().y);
    spritecannon.setPosition(soldadoX+1,spritecannon.getPosition().y+9);
}
void Soldado::setY(float nuevo){
    soldadoY=nuevo;
    spritesol.setPosition(spritesol.getPosition().x,soldadoY);
    spritecannon.setPosition(spritecannon.getPosition().x+1,soldadoY+9);
}
sf::Sprite Soldado::getSprite(){
    return spritesol;
}
void Soldado::updateSoldado(float timeElapsed){

    lastState=newState;

    float xcom=lastState.getX();
    float ycom=lastState.getY();

    /*El soldado solo puede subir arriba o abajo, pero sigue un linea determinada.
    Para ello tenemos que multiplicar la x,y del vector normalizado (resultado
    de restar el punto final con la posicion del jugador) por las actuales junto
    la velocidad y el elapsedTime*/
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Juego::Instance()->getEstado()==0){
        float dirx= 95 - xcom;
        float diry= 145 - ycom;
        float hyp=sqrt((dirx*dirx)+(diry*diry));
        dirx /= hyp;
        diry /= hyp;
        xcom=xcom+(0.3*timeElapsed*dirx);
        ycom=ycom+(0.3*timeElapsed*diry);
        if(xcom<= 95 || ycom<=145 || isnan(xcom) || isnan(ycom)){
            xcom=95;
            ycom=145;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Juego::Instance()->getEstado()==0){
        float dirx= 110 - xcom;
        float diry= 440 - ycom;
        float hyp=sqrt((dirx*dirx)+(diry*diry));
        dirx /= hyp;
        diry /= hyp;
        xcom=xcom+(0.3*timeElapsed*dirx);
        ycom=ycom+(0.3*timeElapsed*diry);
        if(xcom>= 110 || ycom>=440 || isnan(xcom) || isnan(ycom)){
            xcom=110;
            ycom=440;
        }
    }
    /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        xcom=xcom+(0.1*timeElapsed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        xcom=xcom-(0.1*timeElapsed);
    }*/

    //Actualizamos el estado del Soldado
    newState.setX(xcom);
    newState.setY(ycom);

    //cout<< xcom<<","<<ycom <<endl;

}
void Soldado::renderIntSoldado(float percentTick,sf::RenderWindow &window){

    this->setX((lastState.getX()*(1-percentTick))+(newState.getX()*percentTick));
    this->setY((lastState.getY()*(1-percentTick))+(newState.getY()*percentTick));

    float t= (Regla::Instance()->getX()-145)/(620-145);

    angulo=(((-30)-20)*t+(20));
    spritecannon.setRotation(angulo);


    window.draw(spritecannon);
    window.draw(spritesol);
}
float Soldado::getAngulo(){
    return angulo;
}
