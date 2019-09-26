#include <SFML/Graphics.hpp>
#include "State.h"
#include "Soldado.h"
#include <stdio.h>
#include "Juego.h"

#define UPDATE_TICK_TIME (1000/15)

using namespace std;

State updateGameState(float timeElapsed, State &lastState){

        float xcom=lastState.getX();
        float ycom=lastState.getY();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        ycom-=2;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        ycom+=2;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        xcom+=2;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        xcom-=2;
    }

xcom=xcom+(0.1*timeElapsed);
//Pasar los cambios a newState
State nuevo;
nuevo.setX(xcom);
nuevo.setY(ycom);

return nuevo;
}
void interpolar(float percentTick,State &lastState,State &newState){
    Soldado::Instance()->setX((lastState.getX()*(1-percentTick))+(newState.getX()*percentTick));
    Soldado::Instance()->setY((lastState.getY()*(1-percentTick))+(newState.getY()*percentTick));
}

int oldmain()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Cannon Fighter V2");

    sf::View view;
    view.reset(sf::FloatRect(0, 0, 640, 480));

    sf::Texture textura;
    textura.loadFromFile("Texturas/cannon_boy.png");

    sf::Sprite guay(textura);
    guay.scale(0.18f, 0.18f);
    window.setFramerateLimit(60);

    sf::Clock updateClock;
    //sf::Clock contar;

    State newState;
    State lastState;

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(updateClock.getElapsedTime().asMilliseconds()>UPDATE_TICK_TIME){
            lastState=newState;
            float timeElapsed=updateClock.restart().asMilliseconds();
            //cout<<contar.getElapsedTime().asSeconds()<<endl;
            newState=updateGameState(timeElapsed,lastState);
        }
        float aux=updateClock.getElapsedTime().asMilliseconds();
        float percentTick= std::min(1.0f, aux/UPDATE_TICK_TIME);
        interpolar(percentTick,lastState,newState);

        guay.setPosition(Soldado::Instance()->getX(),Soldado::Instance()->getY());
        window.clear();
        window.draw(guay);
        window.display();
    }

    return 0;
}

int main(){
    Juego::Instance()-> iniciarBucle();
}

