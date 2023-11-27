#version 410 core

precision highp float;

layout(quads, fractional_odd_spacing, ccw) in;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

uniform float MIN_DIST;
uniform float MAX_DIST;

out vec3 color;

void main() {
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    vec4 uVec = p01 - p00;
    vec4 vVec = p10 - p00;
    //vec4 normal = normalize(vec4(cross(vVec.xyz, uVec.xyz), 0));

    vec4 p0 = (p01 - p00) * u + p00;
    vec4 p1 = (p11 - p10) * u + p10;
    vec4 p = (p1 - p0) * v + p0;
    
    p.y = 0.1 * (sin(3.14 * p.x * p.x) + cos(3.14 * p.z * p.z));

    vec4 world_position = p * M * V;
    gl_Position = world_position * P;

    float c = 1 - clamp(
            abs(world_position.z - MIN_DIST) / 
            abs(MAX_DIST - MIN_DIST)
            , 0, 1);

    c += 0.2;
    color = vec3(c, c, c);
}