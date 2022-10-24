attribute vec3 vPos;
attribute vec3 vColor;

varying vec4 oColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    oColor = vec4(vColor, 1.0);
}
