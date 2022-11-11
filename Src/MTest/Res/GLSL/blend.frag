//varying vec3 oColor;
//varying vec2 oTexCoord;

//uniform bool uUseTexture;
//uniform sampler2D uTexture1;

//void main(void)
//{
//    gl_FragColor = texture2D(uTexture1, oTexCoord);
//}


#version 330 core
in vec3 oColor;
in vec2 oTexCoord;

uniform bool uUseTexture;
uniform sampler2D uTexture1;

void main(void)
{
    gl_FragColor = texture2D(uTexture1, oTexCoord);
}
