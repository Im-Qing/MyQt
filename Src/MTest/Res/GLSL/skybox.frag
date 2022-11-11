//varying vec3 oTexCoord;

//uniform samplerCube uSkyboxTexture;

//void main(void)
//{
//    gl_FragColor = textureCube(uSkyboxTexture, oTexCoord);
//}


#version 330 core
in vec3 oTexCoord;

uniform samplerCube uSkyboxTexture;

void main(void)
{
    gl_FragColor = textureCube(uSkyboxTexture, oTexCoord);
}
