#include "OBJLoader.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
OBJLoader::OBJLoader()
{

}
RawModel *OBJLoader::Load(QString path)
{
    QVector<QVector3D> tempVertices, outVertices;
    QVector<QVector2D> tempTextures, outTextures;
    QVector<QVector3D> tempNormals, outNormals;

    QVector<int> vertexIndices;
    QVector<int> texIndices;
    QVector<int> normalIndices;

    QFile file(":/res/"+path+".obj");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
        return NULL;
    }

    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(" ", QString::SkipEmptyParts);
        if (line.startsWith("v "))
        {
            tempVertices.append(QVector3D(fields[1].toFloat(), fields[2].toFloat(), fields[3].toFloat()));
        }
        else if (line.startsWith("vt"))
        {
            tempTextures.append(QVector2D(fields[1].toFloat(), fields[2].toFloat()));
        }
        else if (line.startsWith("vn"))
        {
            tempNormals.append(QVector3D(fields[1].toFloat(), fields[2].toFloat(), fields[3].toFloat()));
        }
        else if (line.startsWith("f "))
        {
            for (int i=0; i<3; i++)
            {
                QStringList indeces = fields[i+1].split("/");
                vertexIndices.append(indeces[0].toInt());
                texIndices   .append(indeces[1].toInt());
                normalIndices.append(indeces[2].toInt());
            }
        }
    }
    for(int i=0; i<vertexIndices.size(); i++)
    {
        unsigned int vertexIndex = vertexIndices[i];
        outVertices.append(tempVertices[vertexIndex-1]);
    }
    for(int i=0; i<texIndices.size(); i++)
    {
        unsigned int texIndex = texIndices[i];
        outTextures.append(tempTextures[texIndex-1]);
    }
    for(int i=0; i<normalIndices.size(); i++)
    {
        unsigned int normalIndex = normalIndices[i];
        outNormals.append(tempNormals[normalIndex-1]);
    }
    return new RawModel(outVertices, outTextures, outNormals);
}
