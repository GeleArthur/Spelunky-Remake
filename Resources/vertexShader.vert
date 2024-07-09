#version 300 es

in vec4 VertexPosition;
in vec2 UvCoords;
out vec2 v_GenertingUV;

uniform mat4x4 u_ProjectionMatrix;

void main() {
    gl_Position = VertexPosition * u_ProjectionMatrix;
    v_GenertingUV = UvCoords;
}
