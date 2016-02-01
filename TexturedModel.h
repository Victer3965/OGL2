#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "RawModel.h"

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>


class TexturedModel
{
public:
    TexturedModel(RawModel* model, QString nameTexture);
    void PaintModel(QOpenGLShaderProgram *shader);
    void RotateModel(int xAngle, int yAngle, int zAngle);
    void MoveModel (float dx, float dy);
    QVector3D GetPos();
    void MoveForward(float distance);
private:
    float xRot;
    float yRot;
    float zRot;
    QOpenGLTexture *textures;
    QVector3D pos;
    RawModel* model;

};

#endif // TEXTUREDMODEL_H
