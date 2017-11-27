#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

in vec3 worldPositionv[];

uniform sampler2D point0;
uniform sampler2D point1;
uniform sampler2D point2;
uniform sampler2D intersection;
uniform sampler2D rayOrigin;
uniform mat4 viewProjectionMatrix;
uniform vec3 eyePosition;

void main()
{
    vec2 texCoord = vec2(0.5f, 0.5f);
    vec3 hitPoint0 = texture(point0, texCoord).xyz;
    vec3 hitPoint1 = texture(point1, texCoord).xyz;
    vec3 hitPoint2 = texture(point2, texCoord).xyz;
    vec3 intersectionPoint = texture(intersection, texCoord).xyz;
    vec3 rayOriginPoint = texture(rayOrigin, texCoord).xyz;

    if(distance(worldPositionv[0], hitPoint0) < 0.01f &&
       distance(worldPositionv[1], hitPoint1) < 0.01f &&
       distance(worldPositionv[2], hitPoint2) < 0.01f)
    {
        gl_Position = viewProjectionMatrix * vec4(rayOriginPoint, 1.0);
        EmitVertex();

        gl_Position = viewProjectionMatrix * vec4(intersectionPoint, 1.0);
        EmitVertex();

        EndPrimitive();
    }
}
