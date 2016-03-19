#version 120

attribute vec2 v_xy;
attribute vec2 v_uv;
attribute vec4 v_rgba;

uniform vec2 vw;
uniform vec2 xy;

varying vec2 uv;
varying vec4 rgba;

void main() {
    // OpenGL's coordinate model is too weird for overlays. Fix it.
    vec2 sane_xy = vec2(
        (xy.x * 2) - 1,
        1 - (xy.y * 2)
    );

    gl_Position.xy = (v_xy / vw) + sane_xy;
    gl_Position.zw = vec2(0, 1);

    uv = v_uv;

    rgba = v_rgba;
}
