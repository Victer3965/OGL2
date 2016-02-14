#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <QList>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
struct Triangle
{
    Triangle(float x1, float y1, float z1,
             float x2, float y2, float z2,
             float x3, float y3, float z3)
    {
        V1[0] = x1;
        V1[1] = y1;
        V1[2] = z1;
        V2[0] = x2;
        V2[1] = y2;
        V2[2] = z2;
        V3[0] = x3;
        V3[1] = y3;
        V3[2] = z3;
    }

    Triangle(QVector3D v1, QVector3D v2, QVector3D v3)
    {
        V1[0] = v1.x();
        V1[1] = v1.y();
        V1[2] = v1.z();
        V2[0] = v2.x();
        V2[1] = v2.y();
        V2[2] = v2.z();
        V3[0] = v3.x();
        V3[1] = v3.y();
        V3[2] = v3.z();
    }
    float V1[3],
          V2[3],
          V3[3];
};

class BoundingBox
{
public:
    BoundingBox(QVector<QVector3D> &VertecesModel);
    void createSimpleBox(QVector<QVector3D> &VertecesModel);
    void createComplexBox(QVector<QVector3D> &VertecesModel);
    bool collision(BoundingBox *model2);
    void transform(QMatrix4x4 matrix);
    QList<Triangle> getWorldTriangles() const;

private:
    QList<Triangle> triangles;
    QList<Triangle> worldTriangles;
};

#endif // BOUNDINGBOX_H
