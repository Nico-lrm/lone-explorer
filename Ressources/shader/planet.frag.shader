#version 460 core
layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

struct Material {
    sampler2D texture_diffuse1;

    float opacity;
    float shininess;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform vec3 cameraPos;
uniform float far_plane;
uniform PointLight pointLight[16];
uniform samplerCube depthMap[16];

// Uniform pour def le nombre de pointLight - Sert aussi pour les depthMap & les tangentLightPos;
uniform int numberPointLight;

vec3 gridSamplingDisk[20] = vec3[]
(
    vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1),
    vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
    vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
    vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1),
    vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1)
);

float ShadowCalculation(vec3 fragPos, PointLight light, samplerCube depthTexture)
{
    vec3 fragToLight = fragPos - light.position;
    float currentDepth = length(fragToLight);
    float shadow = 0.0;
    float bias = 0.05;
    int samples = 20;
    float closestDepth = 0.0;
    float viewDistance = length(cameraPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for (int i = 0; i < samples; ++i)
    {
        // A voir comment corriger parce qu'on peut pas changer de depthMap en la passant en paramètre ou avec un index
        closestDepth = texture(depthMap[0], fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;   // undo mapping [0;1]
        if (currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);

    // Visualiser la depthCubemap (debug
    //FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    

    return shadow;
}

vec3 CalcBlinnLight(PointLight light, vec3 normal, samplerCube depthTex, vec3 fragPos, vec3 viewDir)
{
    // Ambient
    vec3 ambient = 0.05 * light.ambient;

    // Diffuse
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse;

    // Specular
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * light.specular;

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / distance * distance;
    diffuse *= attenuation;
    specular *= attenuation;

    // Shadow
    float shadow = ShadowCalculation(fragPos, light, depthTex);

    return (ambient + (1.0 - shadow) * (diffuse + specular));
    //return (ambient + shadow + diffuse + specular);
}


void main()
{
    vec3 color = texture(material.texture_diffuse1, TexCoords).rgb;
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 normal = normalize(Normal);
    vec3 lighting = vec3(0.0);

    for (int i = 0; i < numberPointLight; ++i)
    {
        lighting = lighting + CalcBlinnLight(pointLight[i], normal, depthMap[i], FragPos, viewDir);
    }

    color = color * lighting;
    FragColor = vec4(color, material.opacity);
    
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if (brightness > 1.0)
        BrightColor = vec4(FragColor.rgb, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}