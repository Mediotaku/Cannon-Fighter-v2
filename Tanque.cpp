#include <iostream>
#include <stdio.h>
#include <cmath>
#include "Tanque.h"
#include "Juego.h"
#include <SFML/Graphics.hpp>
using namespace std;

Tanque::Tanque(int linea){
    if (!textanque.loadFromFile("Texturas/tanque.png")){
        std::cerr << "Error cargando la imagen";
        exit(0);
    }
    if (!texmuerte.loadFromFile("Texturas/explosion.png")){
        std::cerr << "Error cargando la imagen";
        exit(0);
    }
    spritetanque.setTexture(textanque);
    spritemuerte.setTexture(texmuerte);
    spritetanque.setTextureRect(sf::IntRect(0, 0, 410, 178));
    spritetanque.setOrigin(205,89);
    spritemuerte.setOrigin(545,470);
    spritetanque.scale(0.16,0.16);
    spritemuerte.scale(0.08,0.08);
    if(linea==1){
    tanqueX=665;
    tanqueY=134;
    }
    if(linea==2){
    tanqueX=665;
    tanqueY=200;
    }
    if(linea==3){
    tanqueX=665;
    tanqueY=268;
    }
    if(linea==4){
    tanqueX=665;
    tanqueY=338;
    }
    if(linea==5){
    tanqueX=665;
    tanqueY=410;
    }
    fila=linea;
    newState.setX(tanqueX);
    newState.setY(tanqueY);
    spritetanque.setPosition(tanqueX,tanqueY);
    spritemuerte.setPosition(tanqueX,tanqueY);
}
float Tanque::getX(){
    return tanqueX;
}
float Tanque::getY(){
    return tanqueY;
}
void Tanque::setX(float nuevo){
    tanqueX=nuevo;
    spritetanque.setPosition(tanqueX,spritetanque.getPosition().y);
    spritemuerte.setPosition(tanqueX,spritemuerte.getPosition().y);
}
void Tanque::setY(float nuevo){
    tanqueY=nuevo;
    spritetanque.setPosition(spritetanque.getPosition().x,tanqueY);
    spritemuerte.setPosition(spritemuerte.getPosition().x,tanqueY);
}
sf::Sprite Tanque::getSprite(){
    return spritetanque;
}
int Tanque::getLinea(){
    return fila;
}
void Tanque::setMuerte(bool nuevo,int indice){
    muerte=nuevo;
    index=indice;
    relojmuerte.restart();
}
void Tanque::updateTanque(float timeElapsed){

    lastState=newState;

    float xcom=lastState.getX();
    float ycom=lastState.getY();
        if(animacion.getElapsedTime().asMilliseconds()>800){
            animacion.restart();
            if(ani==0){
                spritetanque.setTextureRect(sf::IntRect(0, 0, 410, 178));
            }
            if(ani==1){
                spritetanque.setTextureRect(sf::IntRect(0, 178, 410, 178));
            }
            ani++;
            if(ani>1){
                ani=0;
            }
        }
        if(Juego::Instance()->getEstado()==0 && muerte==false){
            xcom=xcom-(0.015*timeElapsed); //0.015
        }
        //xcom=xcom+(0.2*timeElapsed);
        //if(xcom>=620){
         //   xcom=620;
        //}

    //Actualizamos el estado del Tanque
    if(muerte==false){
    newState.setX(xcom);
    newState.setY(ycom);}
}
void Tanque::testmuerte(){
      if(muerte==true && relojmuerte.getElapsedTime().asMilliseconds()>1000){
            Juego::Instance()->borrarTanque(index,fila);
        }
}
void Tanque::renderIntTanque(float percentTick,sf::RenderWindow &window){
    if(muerte==false){
    this->setX((lastState.getX()*(1-percentTick))+(newState.getX()*percentTick));
    this->setY((lastState.getY()*(1-percentTick))+(newState.getY()*percentTick));
    }
    if(Juego::Instance()->getEstado()==0){
    window.draw(spritetanque);
    if(muerte==true){
    window.draw(spritemuerte);
    }}

}
