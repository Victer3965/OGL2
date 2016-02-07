#include "TexturedModel.h"
#include "TexturesManager.h"

#include <QFile>



TexturedModel::TexturedModel(RawModel *model, QString nameTexture, bool createBoundingBox)
{
    if (QFile::exists(":/res/" + nameTexture + ".dds"))
    {
        textures = TexturesManager::getTexture(":/res/" + nameTexture + ".dds");
    }
    else if (QFile::exists(":/res/" + nameTexture + ".jpg"))
    {
        textures = TexturesManager::getTexture(":/res/" + nameTexture + ".jpg");
    }
    else if (QFile::exists(":/res/" + nameTexture + ".jpeg"))
    {
        textures = TexturesManager::getTexture(":/res/" + nameTexture + ".jpeg");
    }
    else textures = TexturesManager::getTexture(":/res/errorTexture.jpg");

//    textures = TexturesManager::getTexture(":/res/"+nameTexture);
    pos.setX(0);
    pos.setY(0);
    pos.setZ(0);
    xRot = 0;
    yRot = 0;
    zRot = 0;
    this->model=model;
    if (createBoundingBox)
    {
        boundingBox = model->calculateBoundingBox();
    }
    else boundingBox = NULL;
}

void TexturedModel::calculateTransformationMatrix()
{
    transformationMatrix.setToIdentity();
    transformationMatrix.translate(pos.x(), pos.y(), pos.z());
    transformationMatrix.rotate(xRot , 1.0f, 0.0f, 0.0f);
    transformationMatrix.rotate(yRot , 0.0f, 1.0f, 0.0f);
    transformationMatrix.rotate(zRot , 0.0f, 0.0f, 1.0f);
}

void TexturedModel::PaintModel(QOpenGLShaderProgram *shader)
{
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
    calculateTransformationMatrix();
    if (boundingBox)
        boundingBox->setTransform(transformationMatrix.data());
}

void TexturedModel::MoveModel(float dx, float dy, float dz)
{    
    pos.setX(pos.x()+dx);
    pos.setY(pos.y()+dy);
    pos.setZ(pos.z()+dz);
    calculateTransformationMatrix();
    if (boundingBox)
        boundingBox->setTransform(transformationMatrix.data());
}

CollisionModel3D* TexturedModel::getBoundingBox()
{
    return boundingBox;
}

QVector3D TexturedModel::GetRot()
{
    return QVector3D(xRot, yRot, zRot);
}

QVector3D TexturedModel::GetPos()
{
    return QVector3D(pos);
}
