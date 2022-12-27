#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

layout(std430, binding = 0) buffer bufferModelMatrices
{
    mat4 models[];
};

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 viewProjMatrix;

void main()
{
    FragPos = vec3(models[gl_InstanceID] * vec4(aPos, 1.0));
    Normal = transpose(inverse(mat3(models[gl_InstanceID]))) * aNormal;
    TexCoords = aTexCoords;
    gl_Position = viewProjMatrix * models[gl_InstanceID] * vec4(aPos, 1.0);
};
