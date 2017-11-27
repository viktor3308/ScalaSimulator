#version 330 core

in vec3 vertexPosition;

out vec3 worldPositionv;

uniform mat4 modelMatrix;
uniform mat4 modelViewProjection;

void main()
{
    worldPositionv = vec3( modelMatrix * vec4( vertexPosition, 1.0 ) );
    gl_Position = modelViewProjection * vec4( vertexPosition, 1.0 );
}
