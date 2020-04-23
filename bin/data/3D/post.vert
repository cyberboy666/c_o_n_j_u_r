#version 150

in vec4 position;
in vec3 normal;
in vec2 texcoord;

out vec2 v_texcoord;

uniform mat4 modelViewProjectionMatrix;

void main() {
    v_texcoord = texcoord;
    gl_Position = modelViewProjectionMatrix * position;
}
