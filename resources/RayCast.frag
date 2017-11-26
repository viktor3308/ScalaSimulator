#version 330 core

flat in vec3 point0g;
flat in vec3 point1g;
flat in vec3 point2g;
flat in vec3 intersectiong;

out vec3 point0;
out vec3 point1;
out vec3 point2;
out vec3 intersection;

void main()
{
    point0 = point0g;
    point1 = point1g;
    point2 = point2g;
    intersection = intersectiong;
}
