#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include "BoundingBox.h"

class RawModel
{
public:
    RawModel(QVector<QVector3D> Verteces, QVector<QVector2D> Textures, QVector<QVector3D> Normals);

    void PaintModel(QOpenGLShaderProgram *shader);

    BoundingBox *getBoungingBox() const;

private:
    int vertexCount;
    QOpenGLBuffer vbo;
    BoundingBox *boungingBox;
};

#endif // RAWMODEL_H
