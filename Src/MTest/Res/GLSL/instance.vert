attribute vec3 vPos;
attribute vec2 vTexCoord;
attribute vec2 vOffset;

varying vec2 oTexCoord;

uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjectionMat;

void main(void)
{
    //gl_Position = uProjectionMat * uViewMat * uModelMat * vec4(vPos, 1.0);
    gl_Position = uProjectionMat * uViewMat * uModelMat * vec4(vPos.x + vOffset.x, vPos.y + vOffset.y, vPos.z, 1.0);
    oTexCoord = vTexCoord;
}
