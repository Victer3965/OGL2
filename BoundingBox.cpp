#include "BoundingBox.h"
#include "Config.h"

extern "C" {
int tri_tri_intersect(float V0[3],float V1[3],float V2[3],
                      float U0[3],float U1[3],float U2[3]);
}

inline QVector3D Transform(const QVector3D& v, QMatrix4x4& m)
{
  return QVector3D(v.x()*m(0,0) + v.y()*m(0,1) + v.z()*m(0,2) + m(0,3),
                   v.x()*m(1,0) + v.y()*m(1,1) + v.z()*m(1,2) + m(1,3),
                   v.x()*m(2,0) + v.y()*m(2,1) + v.z()*m(2,2) + m(2,3));
}

inline QVector3D Transform(const float (&v)[3], QMatrix4x4& m)
{
    float x = v[0]*m(0,0) + v[1]*m(0,1) + v[2]*m(0,2) + m(0,3);
    float y = v[0]*m(1,0) + v[1]*m(1,1) + v[2]*m(1,2) + m(1,3);
    float z = v[0]*m(2,0) + v[1]*m(2,1) + v[2]*m(2,2) + m(2,3);
    return QVector3D(x, y, z);
}

BoundingBox::BoundingBox(QVector<QVector3D> &VertecesModel)
{
    if (config.getSimpleCollision())
        createSimpleBox(VertecesModel);
    else
        createComplexBox(VertecesModel);
}

void BoundingBox::createSimpleBox(QVector<QVector3D> &VertecesModel)
{
    float x1 = VertecesModel[0].x(),
          y1 = VertecesModel[0].y(),
          z1 = VertecesModel[0].z(),
          x2 = VertecesModel[0].x(),
          y2 = VertecesModel[0].y(),
          z2 = VertecesModel[0].z();

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
            z2 = VertecesModel[i].z();
        }
    }
//[1]--------------------------------------

    triangles.append(Triangle(x1, y1, z1,
                              x2, y1, z1,
                              x2, y1, z2));
    triangles.append(Triangle(x2, y1, z2,
                              x1, y1, z2,
                              x1, y1, z1));
//[2]---------------------------------------
    triangles.append(Triangle(x2, y1, z1,
                              x2, y2, z1,
                              x2, y2, z2));
    triangles.append(Triangle(x2, y2, z2,
                              x2, y1, z2,
                              x2, y1, z1));
//[3]--------------------------------------
    triangles.append(Triangle(x2, y2, z1,
                              x1, y2, z1,
                              x1, y2, z2));
    triangles.append(Triangle(x1, y2, z2,
                              x2, y2, z2,
                              x2, y2, z1));
//[4]--------------------------------------
    triangles.append(Triangle(x1, y2, z1,
                              x1, y1, z1,
                              x1, y1, z2));
    triangles.append(Triangle(x1, y1, z2,
                              x1, y2, z2,
                              x1, y2, z1));
//[5]--------------------------------------
    triangles.append(Triangle(x1, y1, z2,
                              x2, y1, z2,
                              x2, y2, z2));
    triangles.append(Triangle(x2, y2, z2,
                              x1, y2, z2,
                              x1, y1, z2));
//[6]--------------------------------------
    triangles.append(Triangle(x1, y2, z1,
                              x2, y2, z1,
                              x2, y1, z1));
    triangles.append(Triangle(x2, y1, z1,
                              x1, y1, z1,
                              x1, y2, z1));
}

void BoundingBox::createComplexBox(QVector<QVector3D> &VertecesModel)
{
    for (int i = 0; i < VertecesModel.size(); i+=3)
    {
        triangles.append(Triangle(VertecesModel[i],
                                  VertecesModel[i+1],
                                  VertecesModel[i+2]));
    }
}

bool BoundingBox::collision(BoundingBox *model2)
{
    for (int i = 0; i < worldTriangles.size(); i++)
    {
        Triangle triangle1 = worldTriangles[i];
        for (int j = 0; j < model2->worldTriangles.size(); j++)
        {
            Triangle triangle2 = model2->worldTriangles[j];
            if(tri_tri_intersect(triangle1.V1, triangle1.V2, triangle1.V3,
                                 triangle2.V1, triangle2.V2, triangle2.V3))
            {
                return true;
            }
        }
    }
    return false;
}

void BoundingBox::transform(QMatrix4x4 matrix)
{
    worldTriangles.clear();
    for (int i = 0; i < triangles.size(); i++)
    {
        worldTriangles.append(Triangle(Transform(triangles[i].V1, matrix),
                                       Transform(triangles[i].V2, matrix),
                                       Transform(triangles[i].V3, matrix)));
    }
}

QList<Triangle> BoundingBox::getWorldTriangles() const
{
    return worldTriangles;
}
