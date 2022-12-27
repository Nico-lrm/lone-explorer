#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 viewProjMatrix;

void main()
{
    TexCoords = aTexCoords;
    Normal = transpose(inverse(mat3(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0f));
    gl_Position = viewProjMatrix * model * vec4(aPos, 1.0);
};
