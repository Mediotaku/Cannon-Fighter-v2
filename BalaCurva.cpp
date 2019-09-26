#include <iostream>
#include <stdio.h>
#include <cmath>
#include "BalaCurva.h"
#include "Soldado.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Juego.h"

# define PI 3.14159265358979323846
using namespace std;

BalaCurva::BalaCurva(){
    if (!texbala.loadFromFile("Texturas/bala.png")){
        std::cerr << "Error cargando la imagen";
        exit(0);
    }
    spritebala.setTexture(texbala);
    spritebala.setOrigin(115,95);
    balaX= Soldado::Instance()->getX()+1;
    balaY= Soldado::Instance()->getY()+9;
    newState.setX(balaX);
    newState.setY(balaY);
    spritebala.setPosition(balaX,balaY);
    spritebala.scale(0.09,0.09);
}

BalaCurva* BalaCurva::instancia=nullptr;

BalaCurva* BalaCurva::Instance()
{
    if(!instancia){
    instancia=new BalaCurva;
    }
    return instancia;
}

float BalaCurva::getX(){
    return balaX;
}
float BalaCurva::getY(){
    return balaY;
}
void BalaCurva::setX(float nuevo){
    balaX=nuevo;
    spritebala.setPosition(balaX,spritebala.getPosition().y);
}
void BalaCurva::setY(float nuevo){
    balaY=nuevo;
    spritebala.setPosition(spritebala.getPosition().x,balaY);
}
sf::Sprite BalaCurva::getSprite(){
    return spritebala;
}
void BalaCurva::updateBalaCurva(){

    lastState=newState;

    float xcom=lastState.getX();
    float ycom=lastState.getY();
    //De esta forma se puede disparar una bala mientras se mueve el soldado
    if(fuego==false){
        this->setX(Soldado::Instance()->getX()+1);
        this->setY(Soldado::Instance()->getY()+9);
     }

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if(fuego==false){
            fuego=true;
            //Los puntos de control de la curva de bezier cuadrática serán el inicial (jugador), el final(indicado por la flecha)
            //y el medio (marcado por la interseccion de las dos lineas surgidas de cada uno de los puntos anteriores una pendiende
            //marcada por el angulo del canon)
            inicioX=balaX;
            inicioY=balaY;
            inicioY2=balaY;
            inicioX2=Regla::Instance()->getX();
            float angulo=abs(Soldado::Instance()->getAngulo()-20);
            float angulo2=180-angulo;
            m=tan ( angulo * PI / 180.0 );
            n = inicioY - (m * inicioX);
            m2=tan ( angulo2 * PI / 180.0 );
            n2 = inicioY2 - (m2 * inicioX2);
            //Punto interseccion de ambos
            corteX=(n2+(-1*n))/(m+(-1*m2));
            corteY=(m2*corteX)+n2;
            corteY=inicioY-(corteY-inicioY);
            //cout<<inicioX<<","<<inicioY<<" "<<inicioX2<<","<<inicioY2<<" "<<corteX<<","<<corteY<<endl;

        }
     }
     if(fuego==true){
        //Interpolar el numero de muestras según la distancia(mas lejos, mas muestras, mas tarda)
        float tt= (inicioX2-inicioX)/(640-inicioX);

        float salto=(((0.015)-0.07)*tt+(0.07));
        t+=salto;
        //Ecuaciones de calculo de un punto dentro de la curva de bezier quadratica
        this->setX( (1 - t) * (1 - t) * inicioX + 2 * (1 - t) * t * corteX + t * t * inicioX2);
        this->setY((1 - t) * (1 - t) * inicioY + 2 * (1 - t) * t * corteY + t * t * inicioY2);
        //cout<<salto<<endl;
     }


    //Actualizamos el estado de la Bala
    newState.setX(xcom);
    newState.setY(ycom);
}
void BalaCurva::reiniciar(){
    fuego=false;
    t=0;
}
void BalaCurva::renderIntBalaCurva(float percentTick, sf::RenderWindow &window){

    //this->setX((lastState.getX()*(1-percentTick))+(newState.getX()*percentTick));
    //this->setY((lastState.getY()*(1-percentTick))+(newState.getY()*percentTick));


    //Prueba de puntos de control de bezier
    /*sf::CircleShape shape1(5);
    shape1.setOrigin(2.5,2.5);
    sf::CircleShape shape2(5);
    shape2.setOrigin(2.5,2.5);
    sf::CircleShape shape3(5);
    shape3.setOrigin(2.5,2.5);
    shape1.setPosition(inicioX,inicioY);
    shape2.setPosition(corteX,corteY);
    shape3.setPosition(inicioX2,inicioY2);
    window.draw(shape1);
    window.draw(shape2);
    window.draw(shape3);*/
    if(fuego==true){
    if(inicioX2!=145 && Juego::Instance()->getEstado()==0){
    window.draw(spritebala);}
    //cout<<t<<endl;
    if(t>=1){
            fuego=false;
            t=0;
        }
    }
}
