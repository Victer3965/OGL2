#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "coldet.h"

class RawModel
{
public:
    RawModel(QVector<QVector3D> Verteces, QVector<QVector2D> Textures, QVector<QVector3D> Normals);

    void PaintModel(QOpenGLShaderProgram *shader);

    CollisionModel3D* calculateBoundingBox();
private:
    int vertexCount;
    QOpenGLBuffer vbo;
    CollisionModel3D* boundingBox;
    QVector<QVector3D> VertecesModel;
};

#endif // RAWMODEL_H
