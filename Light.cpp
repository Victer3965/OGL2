#include "Light.h"

Light::Light(QVector3D position, QVector3D colour)
{
    this->position = position;
    this->colour = colour;
}

QVector3D Light::getPosition() const
{
    return position;
}

void Light::setPosition(const QVector3D &position)
{
    this->position = position;
}

QVector3D Light::getColour() const
{
    return colour;
}

void Light::setColour(const QVector3D &colour)
{
    this->colour = colour;
}

