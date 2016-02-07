#ifndef PHISICSTANKS_H
#define PHISICSTANKS_H

#include "TexturedModel.h"

class PhisicsTanks
{
public:
    PhisicsTanks(TexturedModel* tank);

    void setAcceleration(float accel);

    void setRotation(float zRot);

    void move();

    void stop();

    void cancelMove();

    TexturedModel* Tank;

    QVector3D getPos();

private:
    float zRot;
    float acceleration, speed, rotSpeed;
    float saveSpeed, saveRotSpeed;
    QVector3D savePos;
};

#endif // PHISICSTANKS_H
