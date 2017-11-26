#version 330 core

in vec4 vertexPosition;
in vec3 vertexNormal;

out vec3 positionWorld;
out vec3 positionView;
out vec3 eyePositionv;
out vec3 eyeNormalv;

uniform mat4 mvp;
uniform mat4 modelMatrix;
uniform mat4 modelView;
uniform mat4 inverseViewMatrix;
uniform vec3 eyePosition;

void main()
{
    positionWorld = vec3(modelMatrix * vertexPosition);
    positionView = vec3(modelView * vertexPosition);

    eyePositionv = eyePosition;
    eyeNormalv = normalize(vec3(inverseViewMatrix * vec4(0.0f, 0.0f, -1.0f, 0.0f)));

    gl_Position = mvp * vertexPosition;
}
