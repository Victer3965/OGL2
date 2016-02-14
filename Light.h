#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>



class Light
{
public:
    Light(QVector3D position, QVector3D colour);
    QVector3D getPosition() const;
    void setPosition(const QVector3D &position);

    QVector3D getColour() const;
    void setColour(const QVector3D &colour);

private:
    QVector3D position;
    QVector3D colour;
};

#endif // LIGHT_H
