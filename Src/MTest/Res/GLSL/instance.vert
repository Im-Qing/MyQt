attribute vec3 aPos;
attribute vec2 aTexCoord;
attribute mat4 aInstanceMatrix;

varying vec2 oTexCoord;

uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjectionMat;

void main(void)
{
    gl_Position = uProjectionMat * uViewMat * aInstanceMatrix * vec4(aPos, 1.0);
    oTexCoord = aTexCoord;
}
