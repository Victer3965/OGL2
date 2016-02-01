#ifndef LOADER_H
#define LOADER_H

#include "rawmodel.h"
#include <QOpenGLVertexArrayObject>

class Loader
{
public:
    Loader();
    RawModel* loadToVAO(float* positions, int count);
private:
    QOpenGLVertexArrayObject *createVAO();
    void storeDataOnAttributeList(int attributeNumber, float* data);
    void unbindVAO();
    FloatBuffer storeDatainFloatBuffer(float* data);
    QList<int> vaos;
    QList<int> vbos;
};

#endif // LOADER_H
