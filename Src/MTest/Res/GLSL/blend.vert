//attribute vec3 vPos;
//attribute vec2 vTexCoord;

//varying vec2 oTexCoord;

//uniform mat4 uModelMat;
//uniform mat4 uViewMat;
//uniform mat4 uProjectionMat;

//void main(void)
//{
//    gl_Position = uProjectionMat * uViewMat * uModelMat * vec4(vPos, 1.0);
//    oTexCoord = vTexCoord;
//}


#version 330 core
in vec3 vPos;
in vec2 vTexCoord;

out vec2 oTexCoord;

uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjectionMat;

void main(void)
{
    gl_Position = uProjectionMat * uViewMat * uModelMat * vec4(vPos, 1.0);
    oTexCoord = vTexCoord;
}
