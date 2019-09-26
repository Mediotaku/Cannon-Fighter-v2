#ifndef BALACURVA_H
#define BALACURVA_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "State.h"

class BalaCurva{
    static BalaCurva* instancia;
    float balaX,balaY;
    float angulo;
    State newState;
    State lastState;
    sf::Sprite spritebala;
    sf::Texture texbala;
    bool fuego=false;
    bool retroceso=false;

    //Variables para el calculo de curva de bezier y sus puntos de control
    float m;
    float inicioX;
    float inicioY;
    float n;
    float m2;
    float inicioX2;
    float inicioY2;
    float n2;
    float corteX;
    float corteY;
    float t;

    public:
    BalaCurva();
    static BalaCurva* Instance();
    float getX();
    float getY();
    void setX(float nuevo);
    void setY(float nuevo);
    sf::Sprite getSprite();
    void reiniciar();
    void updateBalaCurva();
    void renderIntBalaCurva(float percentTick, sf::RenderWindow &window);
};
#endif

