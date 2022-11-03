#version 330 core

uniform vec3 lightPos;
uniform vec3 objectColor;

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;

vec3 lightColor = vec3(1.0, 1.0, 1.0);

void main(){
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}