#version 330 core

in vec4 vertexPosition;
in vec3 vertexNormal;

out vec3 positionWorld;
out vec3 positionView;

uniform mat4 mvp;
uniform mat4 modelMatrix;
uniform mat4 modelView;

void main()
{
    positionWorld = vec3(modelMatrix * vertexPosition);
    positionView = vec3(modelView * vertexPosition);

    gl_Position = mvp * vertexPosition;
}
