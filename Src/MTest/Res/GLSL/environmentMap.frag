//varying vec3 oNormal;
//varying vec3 oPosition;

//uniform vec3 uCameraPos;
//uniform samplerCube uSkyboxTexture;

//void main(void)
//{
//    vec3 I = normalize(oPosition - uCameraPos);
//    vec3 R = reflect(I, normalize(oNormal));        //reflect
//    float ratio = 1.00 / 1.52;                        //refract
//    //vec3 R = refract(I, normalize(oNormal), ratio);
//    gl_FragColor = vec4(textureCube(uSkyboxTexture, R).rgb, 1.0);
//}


#version 330 core
in vec3 oNormal;
in vec3 oPosition;

uniform vec3 uCameraPos;
uniform samplerCube uSkyboxTexture;

void main(void)
{
    vec3 I = normalize(oPosition - uCameraPos);
    vec3 R = reflect(I, normalize(oNormal));        //reflect
    float ratio = 1.00 / 1.52;                        //refract
    //vec3 R = refract(I, normalize(oNormal), ratio);
    gl_FragColor = vec4(textureCube(uSkyboxTexture, R).rgb, 1.0);
}
