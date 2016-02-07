#include "RawModel.h"
#include "Shader.h"

RawModel::RawModel(QVector<QVector3D> Verteces, QVector<QVector2D> Textures, QVector<QVector3D> Normals)
{
    VertecesModel = Verteces;
    vertexCount = Verteces.size();
    QVector<GLfloat> vertData;
    for (int i = 0; i < vertexCount; ++i) {
        // vertex position
        vertData.append(Verteces[i].x());
        vertData.append(Verteces[i].y());
        vertData.append(Verteces[i].z());
        // texture coordinate
        vertData.append(Textures[i].x());
        vertData.append(Textures[i].y());
        // normal vector
        vertData.append(Normals[i].x());
        vertData.append(Normals[i].y());
        vertData.append(Normals[i].z());
    }

    vbo.create();
    vbo.bind();
    vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));

}

void RawModel::PaintModel(QOpenGLShaderProgram *shader)
{
    vbo.bind();
    shader->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    shader->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    shader->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 8 * sizeof(GLfloat));
    shader->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 8 * sizeof(GLfloat));
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    vbo.release();
}

CollisionModel3D* RawModel::calculateBoundingBox()
{
    CollisionModel3D* BoundingBox = newCollisionModel3D();

    float x1;
    float y1;
    float z1;

    float x2;
    float y2;
    float z2;

    for (int i = 1; i < VertecesModel.size(); i++)
    {
        if(VertecesModel[i].x() < x1)
        {
            x1 = VertecesModel[i].x();
        }
        if(VertecesModel[i].y() < y1)
        {
            y1 = VertecesModel[i].y();
        }
        if(VertecesModel[i].z() < z1)
        {
            z1 = VertecesModel[i].z();
        }

        if(VertecesModel[i].x() > x2)
        {
            x2 = VertecesModel[i].x();
        }
        if(VertecesModel[i].y() > y2)
        {
            y2 = VertecesModel[i].y();
        }
        if(VertecesModel[i].z() > z2)
        {
            z2 = VertecesModel[i].x();
        }
    }
//[1]--------------------------------------
    BoundingBox->addTriangle(x1, y1, z1,
                             x2, y1, z1,
                             x2, y1, z2);
    BoundingBox->addTriangle(x2, y1, z2,
                             x1, y1, z2,
                             x1, y1, z1);
//[2]---------------------------------------
    BoundingBox->addTriangle(x2, y1, z1,
                             x2, y2, z1,
                             x2, y2, z2);
    BoundingBox->addTriangle(x2, y2, z2,
                             x2, y1, z2,
                             x2, y1, z1);
//[3]--------------------------------------
    BoundingBox->addTriangle(x2, y2, z1,
                             x1, y2, z1,
                             x1, y2, z2);
    BoundingBox->addTriangle(x1, y2, z2,
                             x2, y2, z2,
                             x2, y2, z1);
//[4]--------------------------------------
    BoundingBox->addTriangle(x1, y2, z1,
                             x1, y1, z1,
                             x1, y1, z2);
    BoundingBox->addTriangle(x1, y1, z2,
                             x1, y2, z2,
                             x1, y2, z1);
//[5]--------------------------------------
    BoundingBox->addTriangle(x1, y1, z2,
                             x2, y1, z2,
                             x2, y2, z2);
    BoundingBox->addTriangle(x2, y2, z2,
                             x1, y2, z2,
                             x1, y1, z2);
//[6]--------------------------------------
    BoundingBox->addTriangle(x1, y2, z1,
                             x2, y2, z1,
                             x2, y1, z1);
    BoundingBox->addTriangle(x2, y1, z1,
                             x1, y1, z1,
                             x1, y2, z1);
    BoundingBox->finalize();

    return BoundingBox;
}
