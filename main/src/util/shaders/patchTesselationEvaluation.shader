#version 410 core

precision highp float;

layout(quads, fractional_odd_spacing, ccw) in;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

uniform float MIN_DIST;
uniform float MAX_DIST;

uniform vec3 eye;
uniform vec3 light;

out vec3 n_vec;
out vec3 l_vec;
out vec3 v_vec;

void main() {
    // vertex patch position
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    vec4 p0 = (p01 - p00) * u + p00;
    vec4 p1 = (p11 - p10) * u + p10;
    vec4 p = (p1 - p0) * v + p0;
    
    // final vertex position
    float per = 1;
    float amp = 0.2;
    p.y = amp * (sin(per * p.x * p.x) + cos(per * p.z * p.z));
    vec4 world_position = p * M * V;
    gl_Position = world_position * P;

    // radiance computation
    vec3 n;
    n.x = amp * cos(per * p.x * p.x) * 2 * per * p.x;
    n.y = 0;
    n.z = -amp * sin(per * p.z * p.z) * 2 * per * p.z;
    vec4 l = vec4(light, 1) * V;

    n_vec = normalize(-n);
    l_vec = normalize(l.xyz - world_position.xyz);
    v_vec = normalize(eye - world_position.xyz);

    /*float c = 1 - clamp(
            abs(world_position.z - MIN_DIST) / 
            abs(MAX_DIST - MIN_DIST)
            , 0, 1);

    c += 0.2;
    color = vec3(c, c, c);*/
}