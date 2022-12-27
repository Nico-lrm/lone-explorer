#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

layout(std430, binding = 0) buffer bufferModelMatrices
{
    mat4 models[];
};

uniform mat4 view;
out vec2 TexCoords;
out vec3 FragPos;

uniform mat4 viewProjMatrix;

// Normal
struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform PointLight pointLight[16];
uniform int numberPointLight;
uniform vec3 cameraPos;

// NormalMap
out vec3 TangentLightPos[16];
out vec3 TangentViewPos;
out vec3 TangentFragPos;


void main()
{

    FragPos = vec3(models[gl_InstanceID] * vec4(aPos, 1.0));
    TexCoords = aTexCoords;
    gl_Position = viewProjMatrix * models[gl_InstanceID] * vec4(aPos, 1.0);

    mat3 normalMatrix = transpose(inverse(mat3(models[gl_InstanceID])));

    // Normal Map
    vec3 T = normalize(normalMatrix * aTangent);
    
    // Smooth Normals (smooth shading) 
    vec3 N = normalize(transpose(inverse(mat3(models[gl_InstanceID]))) * normalize(aPos));

    // Flat Normals (flat shading)
    //vec3 N = normalize(normalMatrix * aNormal);

    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);

    mat3 TBN = transpose(mat3(T, B, N));
    for (int i = 0; i < numberPointLight; i++)
    {
        TangentLightPos[i] = TBN * pointLight[i].position;
    }
    TangentViewPos = TBN * cameraPos;
    TangentFragPos = TBN * FragPos;
};
