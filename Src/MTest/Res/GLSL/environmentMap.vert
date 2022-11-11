//attribute vec3 aPos;
//attribute vec3 aNormal;

//varying vec3 oNormal;
//varying vec3 oPosition;

//uniform mat4 uModelMat;
//uniform mat4 uViewMat;
//uniform mat4 uProjectionMat;

//void main(void)
//{
//    //oNormal = mat3(transpose(inverse(uModelMat))) * aNormal;
//    oNormal = aNormal;
//    oPosition = vec3(uModelMat * vec4(aPos, 1.0));
//    gl_Position = uProjectionMat * uViewMat * uModelMat * vec4(aPos, 1.0);
//}


#version 330 core
in vec3 aPos;
in vec3 aNormal;

out vec3 oNormal;
out vec3 oPosition;

uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjectionMat;

void main(void)
{
    oNormal = mat3(transpose(inverse(uModelMat))) * aNormal;
    oPosition = vec3(uModelMat * vec4(aPos, 1.0));
    gl_Position = uProjectionMat * uViewMat * uModelMat * vec4(aPos, 1.0);
}
