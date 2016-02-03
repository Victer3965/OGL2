#include "TexturedModel.h"
#include "math.h"
#include "TexturesManager.h"



TexturedModel::TexturedModel(RawModel *model, QString nameTexture)
{
    textures = TexturesManager::getTexture(nameTexture);
    pos.setX(0);
    pos.setY(0);
    pos.setZ(0);
    this->model=model;
}

void TexturedModel::PaintModel(QOpenGLShaderProgram *shader)
{
    QMatrix4x4 transformationMatrix;
    transformationMatrix.setToIdentity();
    transformationMatrix.translate(pos.x(), pos.y(), pos.z());
    transformationMatrix.rotate(xRot , 1.0f, 0.0f, 0.0f);
    transformationMatrix.rotate(yRot , 0.0f, 1.0f, 0.0f);
    transformationMatrix.rotate(zRot , 0.0f, 0.0f, 1.0f);
    shader->setUniformValue("modelMatrix",transformationMatrix);
    textures->bind();
    model->PaintModel(shader);
    textures->release();

}

void TexturedModel::RotateModel(int xAngle, int yAngle, int zAngle)
{
    xRot += xAngle;
    yRot += yAngle;
    zRot += zAngle;
}

void TexturedModel::MoveModel(float dx, float dy)
{    
    pos.setX(pos.x()+dx);
    pos.setY(pos.y()+dy);
}

QVector3D TexturedModel::GetPos()
{
    return QVector3D(pos);
}

void TexturedModel::MoveForward(float distance)
{
    MoveModel(distance*sin(zRot/180*M_PI),-distance*cos(zRot/180*M_PI));
}
