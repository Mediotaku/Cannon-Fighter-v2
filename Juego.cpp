#include <iostream>
#include <stdio.h>
#include "Juego.h"
#include "Soldado.h"
#include "Regla.h"
#include "BalaCurva.h"
using namespace std;


Juego::Juego(){
    window.create(sf::VideoMode(640, 510), "Cannon Fighter V2");
    view.reset(sf::FloatRect(0, 0, 640, 510));
    if (!texfondo.loadFromFile("Texturas/Fondo/suelo.png")){
        std::cerr << "Error cargando la imagen";
        exit(0);
    }
    retro.loadFromFile("Texturas/ARCADECLASSIC.TTF");

    texfondofijo.loadFromFile("Texturas/fondo.png");
    texbarrera.loadFromFile("Texturas/Fondo/barrera_sprite_1.png");
    texbarrera1.loadFromFile("Texturas/Fondo/roto 1_sprite_1.png");
    texbarrera2.loadFromFile("Texturas/Fondo/roto 2_sprite_1.png");
    texbarrera3.loadFromFile("Texturas/Fondo/roto 3_sprite_1.png");
    texbarrera4.loadFromFile("Texturas/Fondo/roto 4_sprite_1.png");
    texbarrera5.loadFromFile("Texturas/Fondo/roto 5_sprite_1.png");
    barreras.push_back(sf::Sprite(texbarrera1));
    barreras.push_back(sf::Sprite(texbarrera2));
    barreras.push_back(sf::Sprite(texbarrera3));
    barreras.push_back(sf::Sprite(texbarrera4));
    barreras.push_back(sf::Sprite(texbarrera5));
    texvida.loadFromFile("Texturas/vida.png");
    vidas.push_back(sf::Sprite(texvida));
    vidas.push_back(sf::Sprite(texvida));
    vidas.push_back(sf::Sprite(texvida));
    //texguia.loadFromFile("Texturas/Fondo/guias_sprite_1.png");
    fondofijo.setTexture(texfondofijo);
    fondo.setTexture(texfondo);
    barrera.setTexture(texbarrera);
    //guia.setTexture(texguia);
    window.setFramerateLimit(60);

    for(int i=0;i<5;i++){
        balas.push_back(std::unique_ptr<BalaTanque>(new BalaTanque(0,0)));
    }
}

Juego* Juego::instancia=nullptr;

Juego* Juego::Instance()
{
    if(!instancia){
    instancia=new Juego;
    }
    return instancia;
}
int Juego::getEstado(){
    return estado;
}

void Juego::iniciarBucle(){
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
            if(godmode==false){
            godmode=true;}
        }
        if(updateClock.getElapsedTime().asMilliseconds()>UPDATE_TICK_TIME){
            float timeElapsed=updateClock.restart().asMilliseconds();
            //update de todo
            updatemundo();
            Soldado::Instance()->updateSoldado(timeElapsed);
            Regla::Instance()->updateRegla(timeElapsed);
            for (int i = 0; i < (int)balas.size(); ++i){
                //cout<<balas[i]->getX()<<endl;
                balas[i]->updateBalaTanque(timeElapsed);
            }
            for (int i = 0; i < (int)tanques.size(); ++i){
                tanques[i]->updateTanque(timeElapsed);
            }

        }
        float aux=updateClock.getElapsedTime().asMilliseconds();
        float percentTick= std::min(1.0f, aux/UPDATE_TICK_TIME);

        BalaCurva::Instance()->updateBalaCurva();

        window.clear();

        rendermundo();
        BalaCurva::Instance()->renderIntBalaCurva(percentTick, window);
        Soldado::Instance()->renderIntSoldado(percentTick, window);
        Regla::Instance()->renderIntRegla(percentTick, window);
        for (int i = 0; i < (int)balas.size(); ++i){
                balas[i]->renderIntBalaTanque(percentTick, window);
            }
        for (int i = 0; i < (int)tanques.size(); ++i){
                tanques[i]->renderIntTanque(percentTick, window);
            }
        window.display();
    }
    //Borramos los tanques
    /*for (int i = 0; i < (int)tanques.size(); ++i)
    {
        delete tanques[i];
    }*/
    tanques.clear();
    balas.clear();
    barreras.clear();
    vidas.clear();

}

void Juego::updatemundo(){
    if(estado==0){
        fondofijo.setScale(0.75f,0.75f);
        fondofijo.setPosition(-112,-165);
        if(nivel==1){
        fondo.setOrigin(1360,0);
        barrera.setOrigin(1360,0);
        fondo.setScale(0.941f,0.941f);
        barrera.setScale(0.941f,0.941f);

        fondo.setPosition(0,0);
        barrera.setPosition(0,0);
        //guia.setScale(0.941f,0.941f);
        //guia.setPosition(0,0);
        for(int i=0;i<(int)barreras.size();i++){
            barreras[i].setOrigin(1360,0);
            barreras[i].setScale(0.941f,0.941f);
            barreras[i].setPosition(0,0);
        }}
        if(nivel==2){
        fondo.setOrigin(680,0);
        barrera.setOrigin(680,0);
        fondo.setScale(0.941f,0.941f);
        barrera.setScale(0.941f,0.941f);

        fondo.setPosition(0,0);
        barrera.setPosition(0,0);
        //guia.setScale(0.941f,0.941f);
        //guia.setPosition(0,0);
        for(int i=0;i<(int)barreras.size();i++){
            barreras[i].setOrigin(680,0);
            barreras[i].setScale(0.941f,0.941f);
            barreras[i].setPosition(0,0);
        }}
        if(nivel==3){
        fondo.setOrigin(0,0);
        barrera.setOrigin(0,0);
        fondo.setScale(0.941f,0.941f);
        barrera.setScale(0.941f,0.941f);

        fondo.setPosition(0,0);
        barrera.setPosition(0,0);
        //guia.setScale(0.941f,0.941f);
        //guia.setPosition(0,0);
        for(int i=0;i<(int)barreras.size();i++){
            barreras[i].setOrigin(0,0);
            barreras[i].setScale(0.941f,0.941f);
            barreras[i].setPosition(0,0);
        }}
        vidas[0].setScale(0.1,0.1);
        vidas[1].setScale(0.1,0.1);
        vidas[2].setScale(0.1,0.1);
        vidas[0].setPosition(30,483);
        vidas[1].setPosition(60,483);
        vidas[2].setPosition(90,483);
        //Textos
        mododios.setCharacterSize(24);
        mododios.setColor(sf::Color::White);
        mododios.setFont(retro);
        mododios.setString("God Mode");
        mododios.setPosition(30,480);
        //Generacion de tanques inicial en orden aleatorio
        if(progreso<5){
            if(relojTanques.getElapsedTime().asMilliseconds()>4000){
                relojTanques.restart();
                progreso++;
                int index;
                do{
                index=0 + (std::rand() % (int)(4 - (0) + 1));
                }while(lineas[index]==1);
                tanques.push_back(std::unique_ptr<Tanque>(new Tanque(index+1)));
                lineas[index]=1;
            }
        }

        //Deteccion de colision de bala con tanque
        for(int i=0;i<(int)tanques.size();i++){
            if(tanques[i]->getSprite().getGlobalBounds().intersects(BalaCurva::Instance()->getSprite().getGlobalBounds())){
                if(Soldado::Instance()->getY()>tanques[i]->getSprite().getPosition().y-30){
                    if(Soldado::Instance()->getY()<tanques[i]->getSprite().getPosition().y+30){
                         //delete tanques[i];
                         //tanques[i]=placeholder;
                         //sustituir=tanques[i]->getLinea();
                         tanques[i]->setMuerte(true,i);
                          cout<<"pum"<<endl;
                          //relojAnimacion.restart();
                          //auxi=i;
                          //Desaparece la bala
                          BalaCurva::Instance()->reiniciar();
                    }
                }
            }
        }
        for (int i = 0; i < (int)tanques.size(); ++i){
                tanques[i]->testmuerte();
            }
        /*if(auxi!=-1 && relojAnimacion.getElapsedTime().asMilliseconds()>1000){
            tanques[auxi].reset(new Tanque(sustituir));
            auxi=-1;
        }*/
        //El tiempo entre los intentos de disparos de balas tambien es aleatorio
        if(relojBalas.getElapsedTime().asMilliseconds()>randomtiempo){
            for (int i = 0; i < (int)balas.size(); ++i){
            //Comprobamos que la bala no se este moviendo ya
            if(balas[i]->getMover()==false){
                if(lineas[i]==1){
                    //Buscamos en el vector de tanques quien está en la linea i
                    int este;
                    for (int j = 0; j < (int)tanques.size(); ++j){
                        if(tanques[j]->getLinea()==i+1){
                            este=j;
                        }
                    }
                    //Numero aleatorio para decidir si dispara o no este turno
                    int random=0 + (std::rand() % (int)(2 - (0) + 1));
                    if(random==2){
                        balas[i]->setX(tanques[este]->getX());
                        balas[i]->setY(tanques[este]->getY());
                        balas[i]->setMover(true);
                    }
                }
                }
            }
            //Tiempo aleatorio hasta la siguiente iteracion
            relojBalas.restart();
            randomtiempo=0 + (std::rand() % (int)(4000 - (0) + 1));
        }
        //Barreras del juego
        for (int i = 0; i < (int)balas.size(); ++i){
            if(balas[i]->getMover()==true){
            if(balas[i]->getX()<140){
                if(roto[i]!=1){
                roto[i]=1;
                balas[i]->setMover(false);}
            }}
        }
        //Contador de vidas
        for (int i = 0; i < (int)balas.size(); ++i){
            if(balas[i]->getSprite().getGlobalBounds().intersects(Soldado::Instance()->getSprite().getGlobalBounds())){
                if(godmode==false){
                life--;}
                balas[i]->setMover(false);
            }
        }
        if(life==0){
            estado=1;
            gameover.restart();
        }
        for (int i = 0; i < (int)tanques.size(); ++i){
            if(tanques[i]->getX()<190 && nivel!=3){
                estado=3;
                nextlevel.restart();
            }
        }

    }
    if(estado==1){
        if(gameover.getElapsedTime().asMilliseconds()>5000){
            //Vuelta a los valores por defecto
            //tanques.clear();
            life=3;
            for(int h=0;h<5;h++){
                roto[h]=0;
            }
            for (int i = 0; i < (int)tanques.size(); ++i){
                borrarTanque(i,i+1);
            }
            randomtiempo=5000;
            relojBalas.restart();
            nivel=1;
            estado=0;
        }
    }
    if(estado==3){
         if(nextlevel.getElapsedTime().asMilliseconds()>10){
                int hasta;
            if(nivel==3){
                estado=1;
            }
            else{
            if(nivel==1){
                hasta=680;
            }
            if(nivel==2){
                hasta=0;
            }

                if(fondo.getOrigin().x!=hasta){
                    fondo.setOrigin(fondo.getOrigin().x-10,0);
                    barrera.setOrigin(barrera.getOrigin().x-10,0);
                    for(int i=0;i<(int)barreras.size();i++){
                    barreras[i].setOrigin(barreras[i].getOrigin().x-1,0);
                    }
                    for (int i = 0; i < (int)tanques.size(); ++i){
                        tanques[i]->setX(tanques[i]->getX()-10);
                        tanques[i]->setY(tanques[i]->getY()-10);
                    }
                }
                if(fondo.getOrigin().x==hasta){
                    for(int h=0;h<5;h++){
                        roto[h]=0;
                    }
                    for (int i = 0; i < (int)tanques.size(); ++i){
                        borrarTanque(i,i+1);
                    }
                    nivel++;
                    estado=0;
                }
                }


            nextlevel.restart();
         }
    }
}
void Juego::borrarTanque(int i, int sustituir){
    tanques[i].reset(new Tanque(sustituir));
}
void Juego::rendermundo(){
    if(estado==0){
        window.draw(fondofijo);
        window.draw(fondo);
        window.draw(barrera);
        //window.draw(guia);
        for(int i=0;i<(int)barreras.size();i++){
             if(roto[i]==0){
                window.draw(barreras[i]);
             }
        }
        if(godmode==false){
        for(int i=0;i<(int)vidas.size();i++){
            if(i<=life-1){
                window.draw(vidas[i]);
            }
        }}
        else{
            window.draw(mododios);
        }
    }
    if(estado==1){
        window.draw(fondofijo);
        window.draw(fondo);
        window.draw(barrera);
        //window.draw(guia);
        for(int i=0;i<(int)barreras.size();i++){
             if(roto[i]==0){
                window.draw(barreras[i]);
             }
        }
        mododios.setCharacterSize(44);
        mododios.setColor(sf::Color::Red);
        mododios.setFont(retro);
        mododios.setString("Game Over");
        mododios.setPosition(300,300);
        window.draw(mododios);
    }
    if(estado==3){
        window.draw(fondofijo);
        window.draw(fondo);
        window.draw(barrera);
        //window.draw(guia);
        for(int i=0;i<(int)barreras.size();i++){
             if(roto[i]==0){
                window.draw(barreras[i]);
             }
        }
        if(godmode==false){
        for(int i=0;i<(int)vidas.size();i++){
            if(i<=life-1){
                window.draw(vidas[i]);
            }
        }}
        else{
            window.draw(mododios);
        }
    }
}
