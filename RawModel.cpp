#include "RawModel.h"
#include "shader.h"

RawModel::RawModel(QVector<QVector3D> Verteces, QVector<QVector2D> Textures, QVector<QVector3D> Normals)
{
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
