#if __VERSION__ < 330
varying vec4 oColor;
varying vec2 oTexture;
uniform sampler2D uTexture;

void main(void)
{
    //gl_FragColor = vec4(0.0, 1.0, 1.0, 1.0);
    gl_FragColor = oColor;
    gl_FragColor = texture2D(uTexture, oTexture);
}


#else
#version 330 core
layout (location = 0) in vec4 oColor;
layout (location = 1) in vec2 oTexture;
uniform sampler2D uTexture;

void main(void)
{
    //gl_FragColor = vec4(0.0, 1.0, 1.0, 1.0);
    gl_FragColor = oColor;
    gl_FragColor = texture2D(uTexture, oTexture);
}
#endif
