#version 330 core

precision highp float;

out vec4 fragmentColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

in vec3 n_vec;
in vec3 v_vec;
in vec3 l_vec;

void main() {	
	vec3 h_vec = normalize(l_vec + v_vec);

    vec3 radiance = material.ambient;
    float lightCos = max(dot(n_vec, l_vec), 0);
    float viewCos = max(dot(n_vec, h_vec), 0);
    radiance += (material.diffuse * lightCos +
        material.specular * pow(viewCos, material.shininess));

	fragmentColor = vec4(radiance, 1);
}