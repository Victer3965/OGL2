#ifndef SHADER_H
#define SHADER_H

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
#define PROGRAM_LIGHT_POSITION_ATTRIBUTE 2
#define PROGRAM_LIGHT_COLOUR_ATTRIBUTE 3
#define PROGRAM_USE_TEXTURE 4

#include <QOpenGLShaderProgram>
#include "Light.h"

class Shader : public QOpenGLShaderProgram
{
public:
    Shader(QString vshaderName, QString fshaderName, QObject* parent);
    void loadLight(Light light);
};

#endif // SHADER_H
