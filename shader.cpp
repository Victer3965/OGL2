#include "Shader.h"

#include <QFile>

Shader::Shader()
{

}

QOpenGLShaderProgram* Shader::createShader(QString vshaderName, QString fshaderName, QObject *parent)
{


    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, parent);
    {
        QFile file(":/res/Shaders/"+vshaderName+".vert");
        if (file.open(QIODevice::ReadOnly)) {
            QString vsrc = file.readAll();
            if (!vshader->compileSourceCode(vsrc)){
                vshader->log();
            }
        }
    }

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, parent);
    {
        QFile file(":/res/Shaders/"+fshaderName+".frag");
        if (file.open(QIODevice::ReadOnly)) {
            QString fsrc = file.readAll();
            if (!fshader->compileSourceCode(fsrc)){
                fshader->log();
            }
        }
    }

    QOpenGLShaderProgram *tempShader = new QOpenGLShaderProgram(parent);
    tempShader->addShader(vshader);
    tempShader->addShader(fshader);
    tempShader->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    tempShader->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    tempShader->link();

    tempShader->bind();
    tempShader->setUniformValue("texture", 0);

    return tempShader;
}
