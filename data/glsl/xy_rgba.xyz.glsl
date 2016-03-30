#version 120

attribute vec2 v_xy;
attribute vec4 v_rgba;

varying vec4 rgba;

void main() {
    gl_Position = vec4(v_xy, 0, 1);
    rgba = v_rgba;
}
