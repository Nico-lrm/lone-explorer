#version 460 core
in vec4 FragPos;
in vec2 TexCoords;

uniform vec3 lightPos;
uniform float far_plane;
uniform sampler2D texture1;

void main()
{
    vec4 textureColour = texture(texture1, TexCoords);
    if (textureColour.a < 0.5) {
        discard;
    }

    float lightDistance = length(FragPos.xyz - lightPos);

    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / far_plane;

    // write this as modified depth
    gl_FragDepth = lightDistance;
}