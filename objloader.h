#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <QString>
#include <QVector>
#include <QVector2D>
#include <QVector3D>

#include "RawModel.h"

class OBJLoader
{
public:
    OBJLoader();
    //static RawModel ;
    static RawModel *Load(QString path);
};

#endif // OBJLOADER_H
