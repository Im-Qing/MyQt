//varying vec3 oColor;
//varying vec2 oTexCoord;

//uniform bool uUseTexture;
//uniform sampler2D uTexture1;

//void main(void)
//{
//    //gl_FragColor = texture2D(uTexture1, oTexCoord);
//    //反向
//    //gl_FragColor = vec4(vec3(1.0 - texture2D(uTexture1, oTexCoord)), 1.0);
//    //灰度
//    gl_FragColor = texture2D(uTexture1, oTexCoord);
////    float average = 0.2126 * gl_FragColor.r + 0.7152 * gl_FragColor.g + 0.0722 * gl_FragColor.b;
////    gl_FragColor = vec4(average, average, average, 1.0);
//}


#version 330 core
in vec3 oColor;
in vec2 oTexCoord;

uniform bool uUseTexture;
uniform sampler2D uTexture1;

void main(void)
{
    //gl_FragColor = texture2D(uTexture1, oTexCoord);
    //反向
    //gl_FragColor = vec4(vec3(1.0 - texture2D(uTexture1, oTexCoord)), 1.0);
    //灰度
    gl_FragColor = texture2D(uTexture1, oTexCoord);
//    float average = 0.2126 * gl_FragColor.r + 0.7152 * gl_FragColor.g + 0.0722 * gl_FragColor.b;
//    gl_FragColor = vec4(average, average, average, 1.0);
}
