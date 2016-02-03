#include "terrain.h"

Terrain::Terrain()
{

}

RawModel* Terrain::generateTerrain()
{
    int count = vertexCount * vertexCount;
    QVector<QVector3D> vertices(count);
    QVector<QVector3D> normals(count);
    QVector<QVector2D> textureCoords(count);
    int vertexPointer = 0;
    for(int i=0;i<vertexCount;i++){
        for(int j=0;j<vertexCount;j++){
            vertices[vertexPointer] = QVector3D((float)j/((float)vertexCount - 1) * sizeX,
                                                (float)i/((float)vertexCount - 1) * sizeY,
                                                0/*rand()/(float)RAND_MAX*/);
            normals[vertexPointer] = QVector3D(0, 0, 1);
            textureCoords[vertexPointer] = QVector2D((float)j/((float)vertexCount - 1),
                                                       (float)i/((float)vertexCount - 1));
            vertexPointer++;
        }
    }

    QVector<QVector3D> faceVertices;
    QVector<QVector3D> faceNormals;
    QVector<QVector2D> faceTextures;

    for(int gz=0;gz<vertexCount-1;gz++){
        for(int gx=0;gx<vertexCount-1;gx++){
            int topLeft = (gz*vertexCount)+gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1)*vertexCount)+gx;
            int bottomRight = bottomLeft + 1;
            faceVertices.append(vertices[bottomLeft]);
            faceVertices.append(vertices[topLeft]);
            faceVertices.append(vertices[topRight]);
            faceVertices.append(vertices[bottomLeft]);
            faceVertices.append(vertices[topRight]);
            faceVertices.append(vertices[bottomRight]);

            faceNormals.append(normals[bottomLeft]);
            faceNormals.append(normals[topLeft]);
            faceNormals.append(normals[topRight]);
            faceNormals.append(normals[bottomLeft]);
            faceNormals.append(normals[topRight]);
            faceNormals.append(normals[bottomRight]);

            faceTextures.append(textureCoords[bottomLeft]);
            faceTextures.append(textureCoords[topLeft]);
            faceTextures.append(textureCoords[topRight]);
            faceTextures.append(textureCoords[bottomLeft]);
            faceTextures.append(textureCoords[topRight]);
            faceTextures.append(textureCoords[bottomRight]);

        }
    }
    return new RawModel(faceVertices, faceTextures, faceNormals);
}
