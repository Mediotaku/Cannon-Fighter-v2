#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "Tanque.h"
#include "BalaTanque.h"

#define UPDATE_TICK_TIME (1000/15)

class Juego{
    static Juego* instancia;
    sf::Sprite fondo;
    sf::Sprite fondofijo;
    sf::Sprite barrera;
    sf::Sprite guia;
    sf::Sprite bandera;
    sf::Texture texfondo;
    sf::Texture texfondofijo;
    sf::Texture texbarrera;
    sf::Texture texguia;
    sf::Texture texbarrera1;
    sf::Texture texbarrera2;
    sf::Texture texbarrera3;
    sf::Texture texbarrera4;
    sf::Texture texbarrera5;
    sf::Texture texvida;
    sf::Texture texbandera;
    //Vidas actuales
    int life=3;
    //Indicador de barreras rotas
    int roto[5]={0};
    //Nivel para cambiar fondo
    int nivel=1;
    std::vector<sf::Sprite> barreras;
    std::vector<sf::Sprite> vidas;
    sf::RenderWindow window;
    sf::View view;
    sf::Clock updateClock;
    int progreso=0;
    //Indica si nos encontramos en uno de los niveles o en una transicion para reproducirla
    int estado=0;
    //God mode
    bool godmode=false;
    sf::Text mododios;
    sf::Font retro;

    sf::Clock gameover;
    sf::Clock nextlevel;

    //Tanques del juego;
    std::vector<std::unique_ptr<Tanque>> tanques;
    sf::Clock relojTanques;
    int lineas[5]={0};
    int auxi=-1;
    int sustituir;
    //Balas de los tanques
    std::vector<std::unique_ptr<BalaTanque>> balas;
    sf::Clock relojBalas;
    int randomtiempo=5000;
    //int disparos[5]={0};

    public:
    Juego();
    static Juego* Instance();
    int getEstado();
    void borrarTanque(int i, int sustituir);
    void iniciarBucle();
    void updatemundo();
    void rendermundo();
};
#endif
