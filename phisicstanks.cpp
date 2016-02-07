#include <math.h>
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

void PhisicsTanks::setRotation(float zRot)
{
    this->rotSpeed=zRot;
}

void PhisicsTanks::move()
{
    saveSpeed = speed;
    saveRotSpeed = rotSpeed;
    savePos = Tank->GetPos();
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

    zRot = Tank->GetRot().z();
    Tank->MoveModel(speed*sin(zRot/180*M_PI),-speed*cos(zRot/180*M_PI));
    Tank->RotateModel(0, 0, rotSpeed);
}

void PhisicsTanks::stop()
{
    speed = 0;
}

void PhisicsTanks::cancelMove()
{
    Tank->RotateModel(0, 0, -rotSpeed);
    Tank->MoveModel(-speed*sin(zRot/180*M_PI),speed*cos(zRot/180*M_PI));
    speed = saveSpeed;
    rotSpeed = saveRotSpeed;
}

QVector3D PhisicsTanks::getPos()
{
    return Tank->GetPos();
}
