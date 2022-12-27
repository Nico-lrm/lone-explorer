#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

out vec3 TangentLightPos[16];
out vec3 TangentViewPos;
out vec3 TangentFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 viewProjMatrix;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// NormalMap
uniform PointLight pointLight[16];
uniform vec3 cameraPos;
uniform int numberPointLight;

void main()
{
   FragPos = vec3(model * vec4(aPos, 1.0));
   TexCoords = aTexCoords;
   Normal = transpose(inverse(mat3(model))) * normalize(aPos);
   mat3 normalMatrix = transpose(inverse(mat3(model)));

   vec3 T = normalize(normalMatrix * aTangent);

   // Smooth Normals (smooth shading) 
   vec3 N = normalize(transpose(inverse(mat3(model))) * normalize(aPos));

   // Flat Normals (flat shading)
   //vec3 N = normalize(normalMatrix * aNormal);


   vec3 B = cross(T, N);
   T = normalize(T - dot(T, N) * N);

   // Si les modeles ont des UV symetrique
   if (dot(cross(N, T), B) < 0.0)
       T = T * -1.0;

   mat3 TBN = transpose(mat3(T, B, N));
   for (int i = 0; i < numberPointLight; i++)
   {
       TangentLightPos[i] = TBN * pointLight[i].position;
   }
   TangentViewPos = TBN * cameraPos;
   TangentFragPos = TBN * FragPos;

   gl_Position = viewProjMatrix * model * vec4(aPos, 1.0);
};