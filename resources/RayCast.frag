#version 330 core

flat in vec3 point0g;
flat in vec3 point1g;
flat in vec3 point2g;
flat in vec3 intersectiong;
flat in vec3 rayOriging;

out vec3 point0;
out vec3 point1;
out vec3 point2;
out vec3 intersection;
out vec3 rayOrigin;

void main()
{
    point0 = point0g;
    point1 = point1g;
    point2 = point2g;
    intersection = intersectiong;
    rayOrigin = rayOriging;
}
