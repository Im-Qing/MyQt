attribute vec3 vPos;

varying vec3 oTexCoord;

uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjectionMat;

void main(void)
{
    oTexCoord = vPos;
    vec4 pos = uProjectionMat * uViewMat * uModelMat * vec4(vPos, 1.0);
    gl_Position = pos.xyww;
}
