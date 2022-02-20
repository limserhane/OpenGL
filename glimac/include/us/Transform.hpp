#pragma once

#include <glimac/glm.hpp>

using namespace glm;

struct Transform
{
    vec3 position;
    vec3 scale;
    vec3 rotation; //DEGREES

    Transform();

    mat4 getModelMatrix() const;

};
