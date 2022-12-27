#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform sampler2D bloom;
uniform float exposure;

const float offset = 1.0 / 300.0;

vec2 offsets[9] = vec2[](
    vec2(-offset, offset), // top-left
    vec2(0.0f, offset), // top-center
    vec2(offset, offset), // top-right
    vec2(-offset, 0.0f),   // center-left
    vec2(0.0f, 0.0f),   // center-center
    vec2(offset, 0.0f),   // center-right
    vec2(-offset, -offset), // bottom-left
    vec2(0.0f, -offset), // bottom-center
    vec2(offset, -offset)  // bottom-right    
);

float kernel[9] = float[](
    -0, -1, -0,
    -1,  5, -1,
    -0, -1, -0
);

vec3 SharpEffect()
{
    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(hdrBuffer, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    return col;
}

void main()
{
    const float gamma = 1.0;
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;
    vec3 bloomColor = texture(bloom, TexCoords).rgb;

    // Blend des deux textures
    vec3 mapped = mix(hdrColor, bloomColor, 0.125f);
    //hdrColor += bloomColor;

    // exposure tone mapping
    mapped = vec3(1.0) - exp(-mapped * exposure);
    //vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
    // gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));

    FragColor = vec4(mapped, 1.0);
}