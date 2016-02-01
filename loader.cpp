#include "loader.h"

#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

Loader::Loader()
{
 vaos = new QList<int>();
 vbos = new QList<int>();
}

RawModel* Loader::loadToVAO(float *positions, int count)
{
    QOpenGLVertexArrayObject *vao = createVAO();
    storeDataOnAttributeList(0, positions);
    unbindVAO();
    return new RawModel(vao, count/3);
}

QOpenGLVertexArrayObject *Loader::createVAO()
{
    QOpenGLVertexArrayObject *vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();
    return vao;
}

void Loader::storeDataOnAttributeList(int attributeNumber, float *data)
{
    QOpenGLBuffer buffer = QOpenGLBuffer();
    buffer.write(0,data,sizeof(float)*count);
}

void Loader::unbindVAO()
{

}

FloatBuffer Loader::storeDatainFloatBuffer(float *data)
{
    FloatBuffer buffer =
}

