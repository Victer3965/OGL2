#include "Shader.h"

#include <QFile>

Shader::Shader(QString vshaderName, QString fshaderName, QObject *parent)
    :QOpenGLShaderProgram(parent)
{
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, parent);
    {
        QFile file(":/res/Shaders/"+vshaderName+".vert");
        if (file.open(QIODevice::ReadOnly)) {
            QString vsrc = file.readAll();
            if (!vshader->compileSourceCode(vsrc)){
                printf("%s", vshader->log().data());
                exit(1);
            }
        }
    }

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, parent);
    {
        QFile file(":/res/Shaders/"+fshaderName+".frag");
        if (file.open(QIODevice::ReadOnly)) {
            QString fsrc = file.readAll();
            if (!fshader->compileSourceCode(fsrc)){
                printf("%s", fshader->log().data());
                exit(1);
            }
        }
    }
    this->addShader(vshader);
    this->addShader(fshader);
    this->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    this->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    this->bindAttributeLocation("lightPosition", PROGRAM_LIGHT_POSITION_ATTRIBUTE);
    this->bindAttributeLocation("lightColour", PROGRAM_LIGHT_COLOUR_ATTRIBUTE);
    this->bindAttributeLocation("useTexture", PROGRAM_USE_TEXTURE);
    if (!this->link())
    {
        printf("%s", this->log().data());
        exit(1);
    }
    this->bind();
    this->setUniformValue("texture", 0);
}

void Shader::loadLight(Light light)
{
//    this->setUniformValue();
}
