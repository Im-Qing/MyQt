attribute vec3 vPos;
attribute vec4 vColor;
attribute vec2 vTextureCoords;
attribute vec3 vNormal;

varying vec4 oColor;
varying vec2 oTextureCoords;
varying vec3 oNormal;
varying vec3 oFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    oColor = vColor;
    oTextureCoords = vTextureCoords;
    oNormal = vNormal;
    oFragPos = vec3(model * vec4(vPos, 1.0));
}
