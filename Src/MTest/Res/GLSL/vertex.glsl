attribute vec3 vPos;
attribute vec3 vColor;
attribute vec2 vTexCoord;

varying vec3 oColor;
varying vec2 oTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    oColor = vColor;
    oTexCoord = vTexCoord;
}
