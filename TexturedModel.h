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
    TexturedModel(RawModel* model, QString nameTexture, bool createBoundingBox = true);
    void PaintModel(QOpenGLShaderProgram *shader);
    void RotateModel(int xAngle, int yAngle, int zAngle);
    void MoveModel (float dx, float dy, float dz = 0);
    QVector3D GetPos();
    QVector3D GetRot();
    CollisionModel3D* getBoundingBox();
private:
    float xRot;
    float yRot;
    float zRot;
    QOpenGLTexture *textures;
    QVector3D pos;
    RawModel* model;
    QMatrix4x4 transformationMatrix;
    CollisionModel3D* boundingBox;

    void calculateTransformationMatrix();
};

#endif // TEXTUREDMODEL_H
