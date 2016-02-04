#ifndef PHISICSTANKS_H
#define PHISICSTANKS_H

#include "TexturedModel.h"

class PhisicsTanks
{
public:
    PhisicsTanks(TexturedModel* tank);

    void setAcceleration(float accel);

    void move();

private:
    TexturedModel* Tank;

    float acceleration, speed;
};

#endif // PHISICSTANKS_H
