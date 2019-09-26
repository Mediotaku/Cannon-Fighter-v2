#ifndef REGLA_H
#define REGLA_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "State.h"
class Regla{
    static Regla* instancia;
    float flechaX,flechaY;
    State newState;
    State lastState;
    sf::Sprite spriteregla;
    sf::Texture texregla;
    sf::Sprite spriteflecha;
    sf::Texture texflecha;

    public:
    Regla();
    static Regla* Instance();
    float getX();
    float getY();
    void setX(float nuevo);
    void setY(float nuevo);
    void updateRegla(float timeElapsed);
    void renderIntRegla(float percentTick, sf::RenderWindow &window);
};
#endif

