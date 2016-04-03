#version 120

varying vec2 uv;
varying vec4 rgba;

uniform sampler2D tex;

void main() {
    gl_FragColor = rgba;
    gl_FragColor.a *= texture2D(tex, uv).a;
}
