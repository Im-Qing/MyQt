attribute vec3 vPos;
attribute vec3 vColor;

varying vec4 oColor;

void main(void)
{
    gl_Position = vec4(vPos, 1.0);
    oColor = vec4(vColor, 1.0);
}
