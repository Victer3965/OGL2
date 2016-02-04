#include "OBJLoader.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
OBJLoader::OBJLoader()
{

}
RawModel *OBJLoader::Load(QString path)
{
    QVector<QVector3D> temp_vertices, out_vertices;
    QVector<QVector2D> temp_textures, out_textures;
    QVector<QVector3D> temp_normals, out_normals;

    QVector<int> vertexIndices;
    QVector<int> texIndices;
    QVector<int> normalIndices;

    QFile file(":/res/"+path+".obj");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
        return NULL;
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ", QString::SkipEmptyParts);
        if ( line.startsWith("v ") ){
            temp_vertices.append(QVector3D( fields[1].toFloat(), fields[2].toFloat(), fields[3].toFloat()) );
        }
        else if ( line.startsWith("vt") ){
            temp_textures.append(QVector2D( fields[1].toFloat(), fields[2].toFloat()) );
        }else if ( line.startsWith("vn") ){
            temp_normals.append(QVector3D( fields[1].toFloat(), fields[2].toFloat(), fields[3].toFloat()) );
        }else if ( line.startsWith("f ") ){
            for ( int i=0; i<3; i++){
                QStringList indeces = fields[i+1].split("/");
                vertexIndices.append(indeces[0].toInt());
                texIndices   .append(indeces[1].toInt());
                normalIndices.append(indeces[2].toInt());
            }
        }
    }
    for( int i=0; i<vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
        out_vertices.append( temp_vertices[ vertexIndex-1 ] );
    }
    for( int i=0; i<texIndices.size(); i++ ){
        unsigned int texIndex = texIndices[i];
        out_textures.append( temp_textures[ texIndex-1 ] );
    }
    for( int i=0; i<normalIndices.size(); i++ ){
        unsigned int normalIndex = normalIndices[i];
        out_normals.append( temp_normals[ normalIndex-1 ] );
    }
    return new RawModel(out_vertices, out_textures, out_normals);
}
