//varying vec3 oColor;
//varying vec2 oTexCoord;

//uniform bool uUseTexture;
//uniform sampler2D uTexture1;
//uniform sampler2D uTexture2;

//void main(void)
//{
//    if(uUseTexture)
//    {
//        gl_FragColor = mix(texture2D(uTexture1, oTexCoord), texture2D(uTexture2, oTexCoord), 0.5);
//    }
//    else
//    {
//        gl_FragColor = vec4(oColor, 1.0);
//    }
//}


#version 330 core
in vec3 oColor;
in vec2 oTexCoord;

uniform bool uUseTexture;
uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

void main(void)
{
    if(uUseTexture)
    {
        gl_FragColor = mix(texture2D(uTexture1, oTexCoord), texture2D(uTexture2, oTexCoord), 0.5);
    }
    else
    {
        gl_FragColor = vec4(oColor, 1.0);
    }
}
