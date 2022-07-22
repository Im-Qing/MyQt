varying vec4 oColor;
varying vec2 oTexture;
uniform sampler2D uTexture;

void main(void)
{
    gl_FragColor = oColor;
    gl_FragColor = texture2D(uTexture, oTexture);
}
