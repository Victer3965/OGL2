#include "PhisicsTanks.h"

#define SPEED_MAX 1.2

#define FRICTION 0.03

PhisicsTanks::PhisicsTanks(TexturedModel* tank)
{
    acceleration = 0;
    speed = 0;
    this->Tank = tank;
}

void PhisicsTanks::setAcceleration(float accel)
{
    this->acceleration = accel;
}

void PhisicsTanks::move()
{
    if (speed >= 0)
    {
        speed += acceleration - FRICTION;
        if (speed < 0 && acceleration == 0) speed = 0;
    }
    else if (speed <= 0)
    {
        speed += acceleration + FRICTION;
        if (speed > 0 && acceleration == 0) speed = 0;
    }

    if (speed >= SPEED_MAX) speed = SPEED_MAX;

    if (speed <= -SPEED_MAX) speed = -SPEED_MAX;
    Tank->MoveForward(speed);
}
