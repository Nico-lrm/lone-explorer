#version 460 core
layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_emissive1;
};

uniform Material material;
uniform float time;

void main()
{
    float newTime = time / 750;
    vec2 distorded_uv = vec2(texture(material.texture_diffuse1, TexCoords + vec2(-0.5 * (sin(5 * newTime) + 1.5), 0)));
    vec4 color = mix(texture(material.texture_diffuse1, distorded_uv + TexCoords * vec2(2.0, 1.0)), texture(material.texture_diffuse1, TexCoords + vec2(0.5 * (5 * newTime), 0.0)), 0.15);
    //color *= vec4(1.8 * 20, 2.20 * 20, 1.8 * 20, 1.0);
    color *= vec4(80.f, 80.f, 80.f, 1.0);

    FragColor = color;

    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if (brightness > 1.0)
    {
        BrightColor = vec4(FragColor.rgb, 1.0);
    }
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}