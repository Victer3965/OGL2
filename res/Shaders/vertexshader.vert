attribute highp vec4 vertex;
attribute mediump vec4 texCoord;
varying mediump vec4 texc;
uniform highp mat4 ViewMatrix;
uniform highp mat4 projMatrix;
uniform highp mat4 modelMatrix;
void main(void)
{
    gl_Position = projMatrix * ViewMatrix * modelMatrix * vertex;
    texc = texCoord;
    gl_FrontColor = gl_Color;
}
