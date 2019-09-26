#include <iostream>
#include <stdio.h>
#include <cmath>
#include "BalaTanque.h"
#include <SFML/Graphics.hpp>
#include "Juego.h"
using namespace std;


BalaTanque::BalaTanque(float x,float y){
    if (!texbala.loadFromFile("Texturas/bala.png")){
        std::cerr << "Error cargando la imagen";
        exit(0);
    }
    spritebala.setTexture(texbala);
    spritebala.setOrigin(115,95);
    spritebala.setScale(0.05,0.05);
    balaX=x;
    balaY=y;
    newState.setX(balaX);
    newState.setY(balaY);
    spritebala.setPosition(balaX,balaY);

}
float BalaTanque::getX(){
    return balaX;
}
float BalaTanque::getY(){
    return balaY;
}
void BalaTanque::setX(float nuevo){
    balaX=nuevo;
    if(mover==false){
    newState.setX(balaX);}
    spritebala.setPosition(balaX,spritebala.getPosition().y);

}
void BalaTanque::setY(float nuevo){
    balaY=nuevo;
    if(mover==false){
    newState.setY(balaY);}
    spritebala.setPosition(spritebala.getPosition().x,balaY);

}
sf::Sprite BalaTanque::getSprite(){
    return spritebala;
}
void BalaTanque::setMover(bool nuevo){
    mover=nuevo;
    if(nuevo==false){
        this->setX(0);
        this->setY(0);
    }
}
bool BalaTanque::getMover(){

    return mover;
}
void BalaTanque::updateBalaTanque(float timeElapsed){

    lastState=newState;

    float xcom=lastState.getX();
    float ycom=lastState.getY();
    if(mover==true){
        xcom=xcom-(0.5*timeElapsed);
        //cout<<xcom<<endl;
        }

    if(xcom<=100){
        this->setMover(false);
    }
    //Actualizamos el estado de la Bala
     if(mover==true){
    newState.setX(xcom);
    newState.setY(ycom);}

}
void BalaTanque::renderIntBalaTanque(float percentTick,sf::RenderWindow &window){
    if(mover==true && Juego::Instance()->getEstado()==0){
    this->setX((lastState.getX()*(1-percentTick))+(newState.getX()*percentTick));
    this->setY((lastState.getY()*(1-percentTick))+(newState.getY()*percentTick));

    window.draw(spritebala);}
}


