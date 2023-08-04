#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_ViewProjection;

out vec3 v_Position;

void main() {
    v_Position = aPos;
    gl_Position = u_ViewProjection * vec4(aPos, 1.0);
}
