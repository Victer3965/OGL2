varying mediump vec2 texc;

uniform sampler2D texture;
uniform vec3 lightColour;
uniform bool useTexture;

void main(void)
{
    if (useTexture)
        gl_FragColor = texture2D(texture, texc);
    else
        gl_FragColor = gl_Color;
}
