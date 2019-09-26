#include <iostream>
#include <stdio.h>
#include "State.h"
using namespace std;

State::State(){

}
float State::getX(){
    return x;
}
float State::getY(){
    return y;
}
void State::setX(float nuevo){
    x=nuevo;
}
void State::setY(float nuevo){
    y=nuevo;
}
