attribute vec3 aPos;
attribute vec3 aNormal;

varying vec3 oNormal;
varying vec3 oPosition;

uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjectionMat;

void main(void)
{
    //oNormal = mat3(transpose(inverse_mat4(uModelMat))) * aNormal;
    oNormal = aNormal;
    oPosition = vec3(uModelMat * vec4(aPos, 1.0));
    gl_Position = uProjectionMat * uViewMat * uModelMat * vec4(aPos, 1.0);
}
