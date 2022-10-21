varying vec4 oColor;

uniform vec3 unColor;

void main(void)
{
    gl_FragColor = oColor;
    //gl_FragColor = vec4(unColor, 1.0);
}
