#include <iostream>
#include <stdio.h>
#include <cmath>
#include "Regla.h"
#include <SFML/Graphics.hpp>
using namespace std;

Regla::Regla(){
    if (!texregla.loadFromFile("Texturas/Fondo/ruler_sprite_1.png")){
        std::cerr << "Error cargando la imagen";
        exit(0);
    }
    if (!texflecha.loadFromFile("Texturas/flecha.png")){
        std::cerr << "Error cargando la imagen";
        exit(0);
    }
    spriteregla.setTexture(texregla);
    spriteflecha.setTexture(texflecha);
    spriteregla.setScale(0.941f,0.941f);
    spriteregla.setOrigin(1360,0);
    spriteregla.setPosition(0,30);
    flechaX=145; //Rango de movimiento: (145,480)-(620,480)
    flechaY=480;
    newState.setX(flechaX);
    newState.setY(flechaY);
    spriteflecha.setPosition(flechaX,flechaY);
    spriteflecha.setScale(0.1f,0.1f);
    //spriteflecha.setColor(sf::Color(180, 0, 0));
}

Regla* Regla::instancia=nullptr;

Regla* Regla::Instance()
{
    if(!instancia){
    instancia=new Regla;
    }
    return instancia;
}
float Regla::getX(){
    return flechaX;
}
float Regla::getY(){
    return flechaY;
}
void Regla::setX(float nuevo){
    flechaX=nuevo;
    spriteflecha.setPosition(flechaX,spriteflecha.getPosition().y);
}
void Regla::setY(float nuevo){
    flechaY=nuevo;
    spriteflecha.setPosition(spriteflecha.getPosition().x,flechaY);
}
void Regla::updateRegla(float timeElapsed){

    lastState=newState;

    float xcom=lastState.getX();
    float ycom=lastState.getY();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        xcom=xcom+(0.2*timeElapsed);
        if(xcom>=620){
            xcom=620;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        xcom=xcom-(0.2*timeElapsed);
        if(xcom<=145){
            xcom=145;
        }
    }
    //Actualizamos el estado de la Flecha
    newState.setX(xcom);
    newState.setY(ycom);
}
void Regla::renderIntRegla(float percentTick,sf::RenderWindow &window){

    this->setX((lastState.getX()*(1-percentTick))+(newState.getX()*percentTick));
    this->setY((lastState.getY()*(1-percentTick))+(newState.getY()*percentTick));

    window.draw(spriteregla);
    window.draw(spriteflecha);
}
