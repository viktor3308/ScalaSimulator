#version 330 core

in vec3 vertexPosition;
in vec3 vertexNormal;

out vec3 worldPositionv;
out vec3 worldNormalv;

uniform mat4 modelMatrix;
uniform mat3 modelNormalMatrix;
uniform mat4 modelViewProjection;

void main()
{
    worldNormalv = normalize( modelNormalMatrix * vertexNormal );
    worldPositionv = vec3( modelMatrix * vec4( vertexPosition, 1.0 ) );

    gl_Position = modelViewProjection * vec4( vertexPosition, 1.0 );
}
