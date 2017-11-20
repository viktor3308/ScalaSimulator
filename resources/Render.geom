#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 worldPositionv[];
in vec3 worldNormalv[];

uniform sampler2D point0;
uniform sampler2D point1;
uniform sampler2D point2;

out vec3 worldPosition;
out vec3 worldNormal;
out vec4 hitColor;

void main()
{
    vec2 texCoord = vec2(0.5f, 0.5f);
    vec3 hitPoint0 = texture(point0, texCoord).xyz;
    vec3 hitPoint1 = texture(point1, texCoord).xyz;
    vec3 hitPoint2 = texture(point2, texCoord).xyz;

    if(distance(worldPositionv[0], hitPoint0) < 0.01f &&
       distance(worldPositionv[1], hitPoint1) < 0.01f &&
       distance(worldPositionv[2], hitPoint2) < 0.01f)
    {
        for(int i = 0; i < 3; ++i)
        {
            worldPosition = worldPositionv[i];
            worldNormal = worldNormalv[i];
            hitColor = vec4(1.0f, 0.0f, 0.0f, 0.0f);
            gl_Position = gl_in[i].gl_Position;
            EmitVertex();
        }
    }
    else
    {
        for(int i = 0; i < 3; ++i)
        {
            worldPosition = worldPositionv[i];
            worldNormal = worldNormalv[i];
            hitColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
            gl_Position = gl_in[i].gl_Position;
            EmitVertex();
        }
    }
    EndPrimitive();
}
