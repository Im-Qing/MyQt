attribute vec3 vPos;
attribute vec3 vColor;
attribute vec2 vTexCoord;

varying vec3 oColor;
varying vec2 oTexCoord;

uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjectionMat;

void main(void)
{
    gl_Position = uProjectionMat * uViewMat * uModelMat * vec4(vPos, 1.0);
    oColor = vColor;
    oTexCoord = vTexCoord;
}
