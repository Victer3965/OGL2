#include "terrain.h"
#define VERTEX_COUNT 2
#define SIZE 100
Terrain::Terrain()
{

}

RawModel* Terrain::generateTerrain()
{
    int count = VERTEX_COUNT * VERTEX_COUNT;
    QVector<QVector3D> vertices(count);
    QVector<QVector3D> normals(count);
    QVector<QVector2D> textureCoords(count);
    int vertexPointer = 0;
    for(int i=0;i<VERTEX_COUNT;i++){
        for(int j=0;j<VERTEX_COUNT;j++){
            vertices[vertexPointer] = QVector3D((float)j/((float)VERTEX_COUNT - 1) * SIZE,
                                                (float)i/((float)VERTEX_COUNT - 1) * SIZE,
                                                0);
            normals[vertexPointer] = QVector3D(0, 0, 1);
            textureCoords[vertexPointer] = QVector2D((float)j/((float)VERTEX_COUNT - 1),
                                                       (float)i/((float)VERTEX_COUNT - 1));
            vertexPointer++;
        }
    }

    QVector<QVector3D> faceVertices;
    QVector<QVector3D> faceNormals;
    QVector<QVector2D> faceTextures;

    for(int gz=0;gz<VERTEX_COUNT-1;gz++){
        for(int gx=0;gx<VERTEX_COUNT-1;gx++){
            int topLeft = (gz*VERTEX_COUNT)+gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
            int bottomRight = bottomLeft + 1;
            faceVertices.append(vertices[topLeft]);
            faceVertices.append(vertices[bottomLeft]);
            faceVertices.append(vertices[topRight]);
            faceVertices.append(vertices[topRight]);
            faceVertices.append(vertices[bottomLeft]);
            faceVertices.append(vertices[bottomRight]);

            faceNormals.append(normals[topLeft]);
            faceNormals.append(normals[bottomLeft]);
            faceNormals.append(normals[topRight]);
            faceNormals.append(normals[topRight]);
            faceNormals.append(normals[bottomLeft]);
            faceNormals.append(normals[bottomRight]);

            faceTextures.append(textureCoords[topLeft]);
            faceTextures.append(textureCoords[bottomLeft]);
            faceTextures.append(textureCoords[topRight]);
            faceTextures.append(textureCoords[topRight]);
            faceTextures.append(textureCoords[bottomLeft]);
            faceTextures.append(textureCoords[bottomRight]);

        }
    }
    return new RawModel(faceVertices, faceTextures, faceNormals);
}
