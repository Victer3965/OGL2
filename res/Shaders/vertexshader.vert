attribute highp vec3 vertex;
attribute mediump vec2 texCoord;

varying mediump vec2 texc;

uniform highp mat4 ViewMatrix;
uniform highp mat4 projMatrix;
uniform highp mat4 transformationMatrix;
uniform vec3 lightPosition;

void main(void)
{
    vec4 worldPosition = transformationMatrix * vec4(vertex, 1.0);
    gl_Position = projMatrix * ViewMatrix * worldPosition;
    texc = texCoord;
    gl_FrontColor = gl_Color;
}
