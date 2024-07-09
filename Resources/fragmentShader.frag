#version 300 es

precision highp float;
out vec4 outColor;
in vec2 v_GenertingUV;
uniform sampler2D u_texture;

void main()
{
    outColor = texture(u_texture, v_GenertingUV);
}
