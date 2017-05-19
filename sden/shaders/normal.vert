
#version 330 core

layout (location = 0) in vec3 vertPosition;
layout (location = 1) in vec3 vertNormal;
layout (location = 2) in vec2 vertTextureCoord;

out vec2 fragTextureCoord;
out vec3 fragNormal;
out vec3 fragPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // model, view and projection
    gl_Position = projection * view * model * vec4(vertPosition, 1.0f);

    // this postition
    fragPosition = vec3(model * vec4(vertPosition, 1.0f));

    // texture coordinates
    fragTextureCoord = vec2(vertTextureCoord.x, 1.0 - vertTextureCoord.y);

    // texture normal
    fragNormal = mat3(transpose(inverse(model))) * vertNormal;
}
