#ifndef SHADER_H
#define SHADER_H

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

#include <QOpenGLShaderProgram>

class Shader
{
public:
    Shader();
    static QOpenGLShaderProgram *createShader(QString vshaderName, QString fshaderName, QObject* parent);
};

#endif // SHADER_H
