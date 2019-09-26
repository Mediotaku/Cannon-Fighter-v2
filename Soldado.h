#ifndef SOLDADO_H
#define SOLDADO_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "State.h"
#include "Regla.h"
class Soldado{
    static Soldado* instancia;
    float soldadoX,soldadoY;
    float angulo;
    State newState;
    State lastState;
    sf::Sprite spritesol;
    sf::Sprite spritecannon;
    sf::Texture texsol;
    sf::Texture texcannon;

    public:
    Soldado();
    static Soldado* Instance();
    float getX();
    float getY();
    float getAngulo();
    void setX(float nuevo);
    void setY(float nuevo);
    sf::Sprite getSprite();
    void updateSoldado(float timeElapsed);
    void renderIntSoldado(float percentTick, sf::RenderWindow &window);
};
#endif
