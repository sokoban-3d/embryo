#version 120

attribute vec3 v_xyz;
attribute vec2 v_uv;

varying vec2 uv;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(v_xyz, 1);

    uv = vec2(v_uv.x, 1 - v_uv.y);
}
