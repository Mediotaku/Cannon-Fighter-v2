#ifndef TANQUE_H
#define TANQUE_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "State.h"
#include "BalaTanque.h"
class Tanque{
    float tanqueX,tanqueY;
    State newState;
    State lastState;
    sf::Sprite spritetanque;
    sf::Sprite spritemuerte;
    sf::Texture textanque;
    sf::Texture texmuerte;
    sf::Clock animacion;
    sf::Clock relojmuerte;
    int fila; //linea
    int ani=0; //en que fram3 de la animacion te encuentras
    bool muerte=false;
    int index; //posicion en el array

    public:
    Tanque(int linea);
    float getX();
    float getY();
    void setX(float nuevo);
    void setY(float nuevo);
    void setMuerte(bool nuevo,int indice);
    sf::Sprite getSprite();
    int getLinea();
    void testmuerte();
    void updateTanque(float timeElapsed);
    void renderIntTanque(float percentTick, sf::RenderWindow &window);
};
#endif
