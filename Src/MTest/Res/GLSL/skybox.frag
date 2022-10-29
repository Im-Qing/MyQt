varying vec3 oTexCoord;

uniform samplerCube uSkyboxTexture;

void main(void)
{
    gl_FragColor = textureCube(uSkyboxTexture, oTexCoord);
}
