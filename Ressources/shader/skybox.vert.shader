#version 460 core
layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
    TexCoords = aPos;
    vec4 pos = camMatrix * model * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}