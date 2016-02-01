#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLBuffer>

class RawModel
{
public:
    RawModel(QVector<QVector3D> Verteces, QVector<QVector2D> Textures, QVector<QVector3D> Normals);

    void PaintModel();

private:
    int vao;
    int vertexCount;
    QOpenGLBuffer vbo;
};

#endif // RAWMODEL_H