attribute vec3 vPos;
attribute vec4 vColor;
attribute vec2 vTexture;

varying vec4 oColor;
varying vec2 oTexture;

uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    oColor = vColor;
    oTexture = vTexture;
}
