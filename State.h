#ifndef STATE_H
#define STATE_H

#include <stdio.h>
#include <iostream>
class State{
    float x,y;

    public:
    State();
    float getX();
    float getY();
    void setX(float nuevo);
    void setY(float nuevo);
};
#endif
