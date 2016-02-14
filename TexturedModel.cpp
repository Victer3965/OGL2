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
    scale = 1;
    this->model = model;
    if(createBoundingBox)
        this->boundingBox = model->getBoungingBox();
    else
        this->boundingBox = NULL;
}

void TexturedModel::calculateTransformationMatrix()
{
    transformationMatrix.setToIdentity();

    transformationMatrix.translate(pos.x(), pos.y(), pos.z());
    transformationMatrix.rotate(xRot , 1.0f, 0.0f, 0.0f);
    transformationMatrix.rotate(yRot , 0.0f, 1.0f, 0.0f);
    transformationMatrix.rotate(zRot , 0.0f, 0.0f, 1.0f);
    transformationMatrix.scale(scale);
}

void TexturedModel::PaintModel(QOpenGLShaderProgram *shader)
{
    shader->setUniformValue("transformationMatrix",transformationMatrix);
    shader->setUniformValue("useTexture", true);
    textures->bind();
    model->PaintModel(shader);
    textures->release();
    drawBoundingBox(shader);
}

void TexturedModel::Scale(float scale)
{
    this->scale = scale;
    calculateTransformationMatrix();
    if(boundingBox)
        boundingBox->transform(transformationMatrix);

}

void TexturedModel::RotateModel(int xAngle, int yAngle, int zAngle)
{
    xRot += xAngle;
    yRot += yAngle;
    zRot += zAngle;
    calculateTransformationMatrix();
    if(boundingBox)
        boundingBox->transform(transformationMatrix);
}

void TexturedModel::MoveModel(float dx, float dy, float dz)
{    
    pos.setX(pos.x()+dx);
    pos.setY(pos.y()+dy);
    pos.setZ(pos.z()+dz);
    calculateTransformationMatrix();
    if(boundingBox)
        boundingBox->transform(transformationMatrix);
}

BoundingBox* TexturedModel::getBoundingBox()
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

void TexturedModel::drawBoundingBox(QOpenGLShaderProgram *shader)
{
    if(!boundingBox)
        return;
    shader->setUniformValue("useTexture", false);

    QList<Triangle> triangles = boundingBox->getWorldTriangles();

    QMatrix4x4 identityMatrix;
    identityMatrix.setToIdentity();

    shader->setUniformValue("transformationMatrix",identityMatrix);

    glLineWidth(3);
    glColor3f(1.0, 1.0, 1.0);

    for (int i = 0; i < triangles.size(); i++)
    {
        glBegin(GL_LINES);
        glVertex3f(triangles[i].V1[0],triangles[i].V1[1], triangles[i].V1[2]);
        glVertex3f(triangles[i].V2[0],triangles[i].V2[1], triangles[i].V2[2]);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(triangles[i].V2[0],triangles[i].V2[1], triangles[i].V2[2]);
        glVertex3f(triangles[i].V3[0],triangles[i].V3[1], triangles[i].V3[2]);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(triangles[i].V3[0],triangles[i].V3[1], triangles[i].V3[2]);
        glVertex3f(triangles[i].V1[0],triangles[i].V1[1], triangles[i].V1[2]);
        glEnd();
    }
}
