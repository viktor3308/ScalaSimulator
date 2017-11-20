#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 positionWorld[];
in vec3 positionView[];

flat out vec3 point0g;
flat out vec3 point1g;
flat out vec3 point2g;

float sign (vec2 p1, vec2 p2, vec2 p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool pointInTriangle (vec2 pt, vec2 v1, vec2 v2, vec2 v3)
{
    bool b1, b2, b3;

    b1 = sign(pt, v1, v2) < 0.0f;
    b2 = sign(pt, v2, v3) < 0.0f;
    b3 = sign(pt, v3, v1) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}

void main()
{

    vec2 hitPoint = vec2(0.0f, 0.0f);

    if(pointInTriangle(hitPoint, positionView[0].xy, positionView[1].xy, positionView[2].xy))
    {
        point0g = positionWorld[0];
        point1g = positionWorld[1];
        point2g = positionWorld[2];

        gl_Position = vec4(1.0f, -1.0f, gl_in[0].gl_Position.zw);
        EmitVertex();

        point0g = positionWorld[0];
        point1g = positionWorld[1];
        point2g = positionWorld[2];
        gl_Position = vec4(0.0f, 1.0f, gl_in[1].gl_Position.zw);
        EmitVertex();

        point0g = positionWorld[0];
        point1g = positionWorld[1];
        point2g = positionWorld[2];
        gl_Position = vec4(-1.0f, -1.0f, gl_in[2].gl_Position.zw);
        EmitVertex();

        EndPrimitive();
    }
}
