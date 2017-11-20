#version 330 core

flat in vec3 point0g;
flat in vec3 point1g;
flat in vec3 point2g;

out vec3 point0;
out vec3 point1;
out vec3 point2;

void main()
{
    point0 = point0g;
    point1 = point1g;
    point2 = point2g;
}
